
function getparams() {
   var a = document.location.search.slice(1).split("&");
   var ret = {};
   for (i in a) { 
     var tmp = a[i].split("=");
     ret[tmp[0]] = tmp[1];
   }
   return ret;
}


var GET = getparams();

function format_scoreline(item) {

    var l;
    if (item["victory"]) {
        l = '<span class="success label">' + item["name"] +
            "</span>, a glorious victor of level " + item["plev"] +
            ". <small>Last seen on level <b>" + item["dlev"] +
            "</b>. Net worth: <b>" + item["worth"] + "</b> $ZM.</small>";
    } else {
        l = '<span class="success label">' + item["name"] +
            "</span>, level " + item["plev"] + 
            ". <small>Killed on dungeon level <b>" + item["dlev"] + 
            "</b> by " + item["cause"] + 
            ". Net worth: <b>" + item["worth"] + 
            "</b> $ZM.</small>";
    }

    var rcodes = item["rcodes"];
    if (rcodes == 1) {
        l = l + " <small>(Replay codes were used <b>once</b>.)</small>";

    } else if (rcodes > 1) {
        l = l + " <small>(Replay codes were used <b>" + rcodes + "</b> times.)</small>";
    }

    return l;
}

function format_ringstatus(data) {

    if (data["locations"].length == 0) {
        var ts  = data["ts"]*1000;
        var now = (new Date().getTime());
        var dif = now - ts;

        if (ts == 0 || dif >= 7200000) {
            return "Ready to regenerate on dungeon level 1.";
        } else {
            return "Destroyed or in possession since " + (new Date(ts).toLocaleString()) + 
                ".<br/>(" + Math.round((7200000 - dif)/60000) + " minutes left until regeneration.)";
        }
    } else {
        var loc = data["locations"][0];
        var off = loc["dlev_offset"];
        var tab = [
            [ "follow a tunnel due north-west",
              "follow a tunnel due west", 
              "follow a tunnel due south-west" ],
            [ "follow a tunnel due north",
              "main branch", 
              "follow a tunnel due south" ],
            [ "follow a tunnel due north-east",
              "follow a tunnel due east", 
              "follow a tunnel due south-east" ] ];
        return "Found somewhere on dungeon level " + (loc["dlev"] + 1) + " (" + 
            tab[off[0]+1][off[1]+1] +
            ").<br/>It has been there since " + (new Date(data["ts"]*1000).toLocaleString()) + ".";
    }
}


function format_gamestats(data) {
    return "<p>" +
        "Leading cause of death: <b>" + data.kills_raw.cause + "</b>, with <b>" + data.kills_raw.kills + "</b> kills.<br/>" +
        "Leading cause of death, weighed for player level: <b>" + data.kills_plev.cause + "</b>, with <b>" + data.kills_plev.kills + "</b> kills.<br/>" +
        "Leading cause of death, weighed for player net worth: <b>" + data.kills_worth.cause + "</b>, with <b>" + data.kills_worth.kills + "</b> kills.<br/>" +
        "World GDP: <b>" + data.gdp.c + "</b> $ZM.<br/>" + 
        "Average player level: <b>" + data.plev.avg + "</b><br/>" +
        "Median player level: <b>" + data.plev.median + "</b><br/>" +
        "Average dungeon level at time of death: <b>" + data.dlev.avg + "</b><br/>" +
        "Median dungeon level at time of death: <b>" + data.dlev.median + "</b><br/>" +
        "Number of unique player names: <b>" + data.players + "</b><br/>" +
        "Most active player: <b>" + data.most_active.name + "</b>, with <b>" + data.most_active.games + "</b> games played.<br/>" +
        "Most active replay code user: <b>" + data.scummer.name + "</b>, who used a replay code <b>" + data.scummer.streak + "</b> times.<br/>" +
        "Most achievements achieved: <b>" + data.most_achievements.name + "</b> with <b>" + data.most_achievements.number + "</b><br/>" +
        "And the <em>Get Rich Quick Award</em> goes to <b>" + data.got_rich_quick.name + "</b>, who got rich quick with <b>" + 
        data.got_rich_quick.worth + "</b> $ZM and was killed by <b>" + data.got_rich_quick.cause + "</b>" +
        "</p>";
}

function do_highscore() {

    var jsonfile = "hs.json";

    if (GET.hs) {
        jsonfile = GET.hs;
    }

    $.getJSON(jsonfile, {}, 
              function(data) {

                  $.each(data["highscores"]["plev"], function(i,item) {
                      $("<li/>").html(format_scoreline(item)).appendTo("#highscore_plev")
                  });

                  $.each(data["highscores"]["dlev_d"], function(i,item) {
                      $("<li/>").html(format_scoreline(item)).appendTo("#highscore_dlev_d")
                  });

                  $.each(data["highscores"]["dlev_a"], function(i,item) {
                      $("<li/>").html(format_scoreline(item)).appendTo("#highscore_dlev_a")
                  });

                  $.each(data["highscores"]["worth"], function(i,item) {
                      $("<li/>").html(format_scoreline(item)).appendTo("#highscore_worth")
                  });

                  $.each(data["highscores"]["ts"], function(i,item) {
                      $("<li/>").html(format_scoreline(item)).appendTo("#highscore_ts")
                  });

                  $("<span/>").html(data["num_games"]).appendTo("#num_games");

                  $("<p/>").html(format_gamestats(data["stats"])).appendTo("#panel_stats");
              }
             );

    $(".highscores").toggle();
    $("#panel_plev").toggle();
}

function do_ringstatus() {
    var jsonfile = "rs.json";

    if (GET.rs) {
        jsonfile = GET.hs;
    }

    $.getJSON(jsonfile, {},
              function(data) {
                  $("<span/>").html(format_ringstatus(data)).appendTo("#ringstatus");
              }
             );
}
