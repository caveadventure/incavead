
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

function apply_template(element, tmpl, data) {
    $(element).append(Mustache.render($(tmpl).html(), data));
}

function do_highscore() {

    var jsonfile = "hs.json";

    if (GET.hs) {
        jsonfile = GET.hs;
    }

    $.getJSON(jsonfile, {}, 
              function(data) {

                  apply_template("#panel_plev", "#scorelines_tmpl", data.highscores.plev);
                  apply_template("#panel_dlev_d", "#scorelines_tmpl", data.highscores.dlev_d);
                  apply_template("#panel_dlev_a", "#scorelines_tmpl", data.highscores.dlev_a);
                  apply_template("#panel_worth", "#scorelines_tmpl", data.highscores.worth);
                  apply_template("#panel_ts", "#scorelines_tmpl", data.highscores.ts);

                  apply_template("#num_games", "#num_games_tmpl", data);

                  apply_template("#panel_stats", "#stats_tmpl", data.stats);
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

                  var ts = data.ts*1000;
                  var now = (new Date().getTime());
                  var ts_loc = (new Date(ts).toLocaleString());
                  var dif = now - ts;
                  var minutes = Math.round((7200000 - dif)/60000);
                  var regenerate = false;
                  var destroyed = false;
                  var found = false;
                  var dlev;
                  var branch;

                  if (data.locations.length == 0) {
                      if (ts == 0 || dif >= 7200000) {
                          regenerate = true;
                      } else {
                          destroyed = true;
                      }
                  } else {

                      var loc = data.locations[0];
                      var off = loc.dlev_offset;
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

                      dlev = loc.dlev + 1;
                      branch = tab[off[0]+1][off[1]+1];
                      found = true;
                  }

                  var obj = { 'regenerate':regenerate, 'destroyed':destroyed, 'found':found,
                              'ts':ts_loc, 'minutes':minutes, 'dlev':dlev, 'branch':branch };

                  apply_template("#ringstatus", "#ringstatus_tmpl", obj);
              }
             );
}
