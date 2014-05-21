
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


function do_highscore() {

    var jsonfile = "hs.json";

    if (GET.hs) {
        jsonfile = GET.hs;
    }

    $.getJSON(jsonfile, {}, 
              function(data) {

                  $("#panel_plev").append(ich.plev_tmpl(data.highscores));
                  $("#panel_dlev_d").append(ich.dlev_d_tmpl(data.highscores));
                  $("#panel_dlev_a").append(ich.dlev_a_tmpl(data.highscores));
                  $("#panel_worth").append(ich.worth_tmpl(data.highscores));
                  $("#panel_ts").append(ich.ts_tmpl(data.highscores));

                  $("#num_games").append(ich.num_games_tmpl(data));

                  $("#panel_stats").append(ich.stats_tmpl(data.stats));
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

                  $("#ringstatus").append(ich.ringstatus_tmpl(obj));
              }
             );
}
