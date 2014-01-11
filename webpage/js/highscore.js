
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
