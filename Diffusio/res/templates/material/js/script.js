/*
 * Diffusio - Build presentation websites easily
 * https://github.com/diffusio
 * http://diffusio.co
 * 
 * Copyright (C) 2015 
 * 
 * Pierre JACQUIER  
 * http://pierre-jacquier.com
 * 
 * Grégoire DUVAUCHELLE
 * https://github.com/kalterkrieg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

var scripts =  document.getElementsByTagName('script');
var torefreshs = ['script.js'] ; // list of js to be refresh
var key = 1; // change this key every time you want force a refresh
for(var i=0;i<scripts.length;i++){ 
   for(var j=0;j<torefreshs;j++){ 
      if(scripts[i].src && (scripts[i].src.indexOf(torefreshs[j]) > -1)){
        new_src = scripts[i].src.replace(torefreshs[j],torefreshs[j] + 'k=' + key );
        scripts[i].src = new_src; // change src in order to refresh js
      } 
   }
}

//Variables
var last_scrollpos_news, current_tab=1, header_height = document.getElementById('header').offsetHeight;
var tab_indic_left = document.getElementById('tab_' + 1).offsetLeft, tab_indic_width = document.getElementById('tab_'+ 1).offsetWidth;
var social_on = true;
var b_wth, b_hgt;
var all_w_d = document.getElementsByClassName('wide_div');
var all_w_d_l = all_w_d.length;
var z;
var cursorX, cursorY;
var geocoder;
var pos = new Array();
var scrolling = false;
var current_pos=0;
var map;
var address = document.getElementById("map_legend_address").innerHTML;
document.onkeydown = checkKey;
var mapOptions;
try {
    mapOptions = {
      zoom: 15,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    };
}
catch(err) {
    
} 
var marker;

//Initialisation
document.getElementById('tab_1').className = "selectedTab";
var tab_indic_left = document.getElementById('tab_' + 1).offsetLeft, tab_indic_width = document.getElementById('tab_'+ 1).offsetWidth;
document.getElementById('tab_indicator').style.left = document.getElementById('nav_div').offsetLeft + tab_indic_left;
document.getElementById('tab_indicator').style.width = tab_indic_width - 5;
document.getElementById('tab_indicator_m').style.left = tab_indic_left;
document.getElementById('tab_indicator_m').style.width = tab_indic_width;
document.getElementById('a_tab_' + 1).style.color = 'white';
document.getElementById('a_tab_' + 2).style.color = '#bdedf3';
document.getElementById('a_tab_' + 3).style.color = '#bdedf3';
document.getElementById('tab_indicator').style.transition = 'all 0s';
getViewport();
setBandSize();
document.getElementById("open_link").href = "https://www.google.fr/maps/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");
document.getElementById("open_link_1").href = "https://www.google.fr/maps/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");
document.getElementById("open_link_2").href = "https://www.here.com/search/" + address.replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace("<br>"," ").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+").replace(" ","+");

if((""+window.location+"").indexOf("#") == -1 && (""+window.location+"").indexOf("#more") == -1 && (""+window.location+"").indexOf("#news") == -1 && (""+window.location+"").indexOf("#presentation") == -1)
    window.location += "#presentation";
var index = (""+window.location+"").indexOf("#");
var root;
if(index != -1)
    root = (""+window.location+"").substring(0,index);
else
    root = (""+window.location+"")
if((""+window.location+"") == root + "#presentation")
    setVisibleNotVisibleNotVisible(1,2,3);
if((""+window.location+"") == root + "#news")
    setVisibleNotVisibleNotVisible(2,3,1)
if((""+window.location+"") == root + "#more")
    setVisibleNotVisibleNotVisible(3,2,1)

    
//Fonctions
function getViewport() {


 // the more standards compliant browsers (mozilla/netscape/opera/IE7) use window.innerWidth and window.innerHeight
 if (typeof window.innerWidth != 'undefined') {
   b_wth = window.innerWidth,
   b_hgt = window.innerHeight
 }

// IE6 in standards compliant mode (i.e. with a valid doctype as the first line in the document)
 else if (typeof document.documentElement != 'undefined'
 && typeof document.documentElement.clientWidth !=
 'undefined' && document.documentElement.clientWidth != 0) {
    b_wth = document.documentElement.clientWidth,
    b_hgt = document.documentElement.clientHeight
 }

 // older versions of IE
 else {
   b_wth = document.getElementsByTagName('body')[0].clientWidth,
   b_hgt = document.getElementsByTagName('body')[0].clientHeight
 }
 return [b_wth, b_hgt];
}

function setIndicator()
{
    var left = document.getElementById('tab_' + current_tab).offsetLeft;
    var width = document.getElementById('tab_'+ current_tab).offsetWidth;
    document.getElementById('tab_indicator').style.left = document.getElementById('nav_div').offsetLeft + left;
    document.getElementById('tab_indicator').style.width = width;
    document.getElementById('tab_indicator_m').style.left = left;
    document.getElementById('tab_indicator_m').style.width = width;
}

function setVisibleNotVisibleNotVisible(visible, not_visible1, not_visible2,scroll_to_top)
{
    current_tab = visible;
    if(typeof(scroll_to_top) == 'undefined')
        scroll_to_top = true;
    setIndicator();
    document.getElementById('tab_indicator').style.transition = 'all 0.5s';
    document.getElementById('a_tab_' + visible).style.color = 'white';
    document.getElementById('a_tab_' + not_visible1).style.color = 'rgb(230,230,230)';
    document.getElementById('a_tab_' + not_visible2).style.color = 'rgb(230,230,230)';
    switch(visible)
    {	
        case 1:
            for(var i=1;i<=3;i++)
            {
                document.getElementById("content_" + i).style.left = b_wth*(i-1);
                document.getElementById("content_" + i).style.marginLeft = 0;
            }
            document.getElementById('site_title').style.background = 'transparent';
            document.getElementById('nav_div').style.background = 'transparent';
            document.getElementById('header').style.background = 'transparent';
            document.getElementById('header').className = 'no_shadow';
            document.getElementById('nav_div').className = 'no_shadow';
            document.body.style.overflowY = "hidden";
            document.getElementById("pres_progress").style.opacity = 1;
            window.location = root + "#presentation"
            break;
        case 2:
            document.getElementById("content_2").style.left = 0;
            document.getElementById("content_2").style.marginLeft = 0;
            document.getElementById("content_1").style.marginLeft = (-1)*b_wth;
            document.getElementById("content_3").style.left = b_wth;
            document.getElementById('site_title').style.background = '#e91e63';
            document.getElementById('nav_div').style.background = '#e91e63';
            document.getElementById('header').className = '';
            document.body.style.overflowY = "auto";
            document.getElementById("pres_progress").style.opacity = 0;
            window.location = root + "#news"
            break;
        case 3:
            document.getElementById("content_3").style.left = 0;
            document.getElementById("content_2").style.left = 0;
            document.getElementById("content_3").style.marginLeft = 0;
            document.getElementById("content_1").style.marginLeft = (-2)*b_wth;
            document.getElementById("content_2").style.marginLeft = -b_wth;
            document.getElementById('site_title').style.background = '#607d8b';
            document.getElementById('nav_div').style.background = '#607d8b';
            document.getElementById('header').className = '';
            document.body.style.overflowY = "auto";
            document.getElementById("pres_progress").style.opacity = 0;
            window.location = root + "#more"
            break;
    }	
    if(scroll_to_top)
        document.body.scrollTop = 0;
}

function mouse_position(e)
{
    cursorX = e.clientX;
    cursorY = e.clientY;
}


function openCircleNews(id)
{
    document.getElementById('news_' + id).style.transition = "transform 0.6s, z-index 0s";
    document.getElementById('circle_news').style.top = cursorY + document.body.scrollTop;
    document.getElementById('circle_news').style.left = cursorX;
    document.getElementById('circle_news').style.opacity = 1;
    document.getElementById('news_' + id).style.zIndex = 160;
    document.body.style.overflow='hidden';
    document.getElementById('header2').style.top = 0;
    document.getElementById('news_' + id).style.maxHeight = document.documentElement.clientHeight - 50;
    document.getElementById('news_' + id).style.overflow = 'auto';
    function scrollFunc(e) {
        if ( typeof scrollFunc.x == 'undefined' ) {
            scrollFunc.x=document.getElementById('news_' + id).scrollTop;
        }
        var diffX=scrollFunc.x-document.getElementById('news_' + id).scrollTop;
        if( diffX<0 ) {
            document.getElementById('news_' + id).style.top=-50;
        } else if( diffX>0 ) {
            document.getElementById('news_' + id).style.top=0;
        } else {
            // First scroll event
        }
        scrollFunc.x=document.getElementById('news_' + id).scrollTop;
    }
    document.getElementById('news_' + id).onscroll=scrollFunc
    if(document.getElementById('news_'+id).getBoundingClientRect().top < 0)
    {
        document.getElementById('news_' + id).style.transform = 'translate3d(0,'+ (-document.getElementById('news_'+id).getBoundingClientRect().top + 50) + 'px,0)';
        document.getElementById('news_' + id).style.WebkitTransform = 'translate3d(0,'+ (-document.getElementById('news_'+id).getBoundingClientRect().top + 50) + 'px,0)';
    }
    else
    {
        document.getElementById('news_' + id).style.transform = 'translate3d(0,-'+ (document.getElementById('news_'+id).getBoundingClientRect().top - 50) + 'px,0)';
        document.getElementById('news_' + id).style.WebkitTransform = 'translate3d(0,-'+ (document.getElementById('news_'+id).getBoundingClientRect().top - 50) + 'px,0)';
    }
    document.getElementById('circle_news').style.transition = 'transform 0.5s';
    document.getElementById('FAB_close').style.transition = '0.6s 0.5s';
    document.getElementById('FAB_close').style.left = 45;
    document.getElementById('FAB_close').onclick = function (){closeCircleNews(id);};
    document.getElementById('circle_news').style.transform = 'scale(900)';
    document.getElementById('circle_news').style.WebkitTransform = 'scale(900)';
    document.getElementById('news_content_' + (id)).style.height = 'auto';
    document.getElementById('news_content_' + (id)).style.opacity = 1;
    var left_m = b_wth > 600 ? '8%' : "1.6%";
    document.getElementById('FAB_close').style.left = left_m;
    var all_read = document.getElementsByClassName('read_more');
    var read_lgt = all_read.length;
    var j;
    for(j=0;j<read_lgt;j++)
    {
        all_read[j].style.display = 'none';
    }
}
function closeCircleNews(id)
{
    document.getElementById('news_' + id).style.transform = 'translate3d(0,0px,0)';
    document.getElementById('news_' + id).style.WebkitTransform = 'translate3d(0,0px,0)';
    document.getElementById('circle_news').style.transition = 'transform 0.3s 0.3s';
    document.body.style.overflowY = 'auto';
    document.getElementById('header2').style.top = -150;
    document.getElementById('news_content_' + (id)).style.height = 0;
    document.getElementById('news_content_' + (id)).style.opacity = 0;
    document.getElementById('news_' + id).style.transition = "transform 0.6s, z-index 0s 0.6s";
    document.getElementById('news_' + id).style.zIndex = 2;
    document.getElementById('news_' + id).style.overflow = 'hidden';
    document.getElementById('FAB_close').style.transition = '0.5s';
    document.getElementById('FAB_close').style.left = '-75px';
    document.getElementById('circle_news').style.transform = 'scale(0.0033)';
    document.getElementById('circle_news').style.WebkitTransform = 'scale(0.0033)';
    var all_read = document.getElementsByClassName('read_more');
    var read_lgt = all_read.length;
    var j;
    for(j=0;j<read_lgt;j++)
    {
        all_read[j].style.display = 'block';
    }
}
function setContentWidth()
{
    b_wth = document.documentElement.clientWidth + 50;
    b_hgt = document.documentElement.clientHeight;
    for(var i=1;i<=3;i++)
    {
        document.getElementById("content_" + i).style.width = b_wth - 50;
        document.getElementById("content_" + i).style.left = b_wth*(i-1);
    }
}

function updateAll()
{
    detectSwipe("body",findSwipeDirection);
    getViewport();
    setContentWidth();
    setBandSize();
    switch(current_tab)
    {
        case 1:
            not_visible1 = 2;
            not_visible2 = 3;
            break;
        case 2:
            not_visible1 = 1;
            not_visible2 = 3;
            break;
        case 3:
            not_visible1 = 1;
            not_visible2 = 2;
            break;
    }
    setVisibleNotVisibleNotVisible(current_tab, not_visible1, not_visible2,false);
    setIndicator();
    setPresIndic();
}
updateAll();

function setPresIndic()
{
    document.getElementById("pres_progress").style.top = b_hgt / 2  - document.getElementById("pres_progress").offsetHeight;   
}

function setBandSize()
{
    getViewport();
    all_w_d[0].style.height = b_hgt * 0.8;
    for (z=1;z<all_w_d_l;z++)
    {
        all_w_d[z].style.height= b_hgt;
    }
    pos[0] = 0;
    pos[1] = document.getElementById("w_d_1").offsetTop + document.getElementById("w_d_1").offsetHeight;
    pos[2] = document.getElementById("w_d_2").offsetTop + document.getElementById("w_d_2").offsetHeight;
}

function initialize() {
    geocoder = new google.maps.Geocoder();
    map = new google.maps.Map(document.getElementById('map_canvas'), mapOptions);
    codeAddress();
}

function codeAddress() {
    geocoder.geocode( { 'address': address}, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        map.setCenter(results[0].geometry.location);
        if(marker)
          marker.setMap(null);
        marker = new google.maps.Marker({
            map: map,
            position: results[0].geometry.location,
            draggable: true
        });

      }
    });
}


function checkKey(e) {
    e = e || window.event;
    if (e.keyCode == '38') {
        if(current_tab==1)
        {
            movePresentation(current_pos - 1); 
        }
    }
    else if (e.keyCode == '40') {
       if(current_tab==1)
        {
           movePresentation(current_pos + 1); 
        }
    }
    else if (e.keyCode == '37') {
       // left arrow
        switch(current_tab)
        {
            case 1:
                setVisibleNotVisibleNotVisible(3,1,3);
                break;
            case 2:
                setVisibleNotVisibleNotVisible(1,2,3);
                break;
            case 3:
                setVisibleNotVisibleNotVisible(2,1,3);
                break;
        }
    }
    else if (e.keyCode == '39') {
       // right arrow
        switch(current_tab)
        {
            case 1:
                setVisibleNotVisibleNotVisible(2,1,3);
                break;
            case 2:
                setVisibleNotVisibleNotVisible(3,1,2);
                break;
            case 3:
                setVisibleNotVisibleNotVisible(1,3,2);
                break;
        }
    }
        return false;
}


 function MouseScroll (event) 
{
        if(current_tab = 1)
        {
            var rolled = 0;
            if ('wheelDelta' in event) {
                rolled = event.wheelDelta;
            }
            else {  // Firefox
                    // The measurement units of the detail and wheelDelta properties are different.
                rolled = -40 * event.detail;
            }
            
            if(rolled < 0)
                movePresentation(current_pos + 1); 
            else
                movePresentation(current_pos - 1); 
        }
}

function Init () {
        // for mouse scrolling in Firefox
    var elem = document.getElementById("content_1");
    if (elem.addEventListener) {    // all browsers except IE before version 9
            // Internet Explorer, Opera, Google Chrome and Safari
        elem.addEventListener ("mousewheel", MouseScroll, false);
            // Firefox
        elem.addEventListener ("DOMMouseScroll", MouseScroll, false);
    }
    else {
        if (elem.attachEvent) { // IE before version 9
            elem.attachEvent ("onmousewheel", MouseScroll);
        }
    }
}
Init();


function movePresentation(pos_to_go)
{
    if(scrolling == false)
    {
    current_pos = pos_to_go;  
    var i;
    switch(pos_to_go)
       {
           case 0:
                smoothScrollTo(pos[0]);
                document.getElementById("FAB_pres").style.opacity = 1;
                document.getElementById('header').style.background = "#009688";
                document.getElementById("pres_progress_0").getElementsByTagName("DIV")[0].style.background = "white";
                document.getElementById("pres_progress_1").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_2").getElementsByTagName("DIV")[0].style.background = "transparent";
               document.getElementById("indic_1").style.border = "solid white 1px"; 
               document.getElementById("indic_2").style.border = "solid white 1px"; 
               document.getElementById("indic_3").style.border = "solid white 1px"; 
                break;
           case 1:
                smoothScrollTo(pos[1]);
                document.getElementById('header').style.background = "gray";
                document.getElementById("FAB_pres").style.opacity = 0;
                document.getElementById("pres_progress_0").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_1").getElementsByTagName("DIV")[0].style.background = "grey";
                document.getElementById("pres_progress_2").getElementsByTagName("DIV")[0].style.background = "transparent";
               document.getElementById("indic_1").style.border = "solid grey 1px"; 
               document.getElementById("indic_2").style.border = "solid grey 1px"; 
               document.getElementById("indic_3").style.border = "solid grey 1px"; 
                break;
           case 2:
                smoothScrollTo(pos[2]);
                document.getElementById('header').style.background = "#E61875";
                document.getElementById("FAB_pres").style.opacity = 0;
                document.getElementById("pres_progress_0").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_1").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_2").getElementsByTagName("DIV")[0].style.background = "white";
               document.getElementById("indic_1").style.border = "solid white 1px"; 
               document.getElementById("indic_2").style.border = "solid white 1px"; 
               document.getElementById("indic_3").style.border = "solid white 1px"; 
                break;
           case -1:
                smoothScrollTo(pos[2]);
                document.getElementById('header').style.background = "#E61875";
                document.getElementById("FAB_pres").style.opacity = 0;  
               current_pos = 2;
                document.getElementById("pres_progress_0").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_1").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_2").getElementsByTagName("DIV")[0].style.background = "white";
               document.getElementById("indic_1").style.border = "solid white 1px"; 
               document.getElementById("indic_2").style.border = "solid white 1px"; 
               document.getElementById("indic_3").style.border = "solid white 1px"; 
               break;
            case 3:
                smoothScrollTo(pos[0]);
                document.getElementById('header').style.background = "#009688";
                document.getElementById("FAB_pres").style.opacity = 1;  
               current_pos = 0;
                document.getElementById("pres_progress_0").getElementsByTagName("DIV")[0].style.background = "white";
                document.getElementById("pres_progress_1").getElementsByTagName("DIV")[0].style.background = "transparent";
                document.getElementById("pres_progress_2").getElementsByTagName("DIV")[0].style.background = "transparent";
               document.getElementById("indic_1").style.border = "solid white 1px"; 
               document.getElementById("indic_2").style.border = "solid white 1px"; 
               document.getElementById("indic_3").style.border = "solid white 1px"; 
               break;
       }
    }
}

function detectSwipe(el,func) {
      swipe_det = new Object();
      swipe_det.sX = 0;
      swipe_det.sY = 0;
      swipe_det.eX = 0;
      swipe_det.eY = 0;
      var min_x = 600;  //min x swipe for horizontal swipe
      var max_x = 300;  //max x difference for vertical swipe
      var min_y = 200;  //min y swipe for vertical swipe
      var max_y = 600;  //max y difference for horizontal swipe
      var direc = "";
      ele = document.body;
      ele.addEventListener('touchstart',function(e){
        var t = e.touches[0];
        swipe_det.sX = t.screenX; 
        swipe_det.sY = t.screenY;
      },false);
      ele.addEventListener('touchmove',function(e){
       if(current_tab==1) e.preventDefault();
        var t = e.touches[0];
        swipe_det.eX = t.screenX; 
        swipe_det.eY = t.screenY;    
      },false);
      ele.addEventListener('touchend',function(e){
        //horizontal detection
        if ((((swipe_det.eX - min_x > swipe_det.sX) || (swipe_det.eX + min_x < swipe_det.sX)) && ((swipe_det.eY < swipe_det.sY + max_y) && (swipe_det.sY > swipe_det.eY - max_y)))) {
          if(swipe_det.eX > swipe_det.sX) direc = "r";
          else direc = "l";
        }
        //vertical detection
        if ((((swipe_det.eY - min_y > swipe_det.sY) || (swipe_det.eY + min_y < swipe_det.sY)) && ((swipe_det.eX < swipe_det.sX + max_x) && (swipe_det.sX > swipe_det.eX - max_x)))) {
          if(swipe_det.eY > swipe_det.sY) direc = "d";
          else direc = "u";
        }
    
        if (direc != "") {
          if(typeof func == 'function') func(el,direc);
        }
        direc = "";
      },false);  
}


function findSwipeDirection(el,d)
{
    if(current_tab == 1)
    {
        if(d=="u")
             movePresentation(current_pos + 1);
        if(d=="d")
             movePresentation(current_pos - 1);
    }
    if(d=="l")
    {
        switch(current_tab)
        {
            case 1:
                setVisibleNotVisibleNotVisible(2,1,3);
                break;
            case 2:
                setVisibleNotVisibleNotVisible(3,1,3);
                break;
            case 3:
                setVisibleNotVisibleNotVisible(1,2,3);
                break;
        }   
    }
    if(d=="r")
    {
        switch(current_tab)
        {
            case 1:
                setVisibleNotVisibleNotVisible(3,1,3);
                break;
            case 2:
                setVisibleNotVisibleNotVisible(1,2,3);
                break;
            case 3:
                setVisibleNotVisibleNotVisible(2,1,3);
                break;
        }   
    }
}


function animation(effectFrame, duration, from, to, easing, framespacing) {
    var start = Date.now(),
        change = to - from;
    duration = duration || 1000;
    if(typeof from === 'function') {
        easing = from;
        from = 0;
    }
    easing = easing || function(x, t, b, c, d) { return c*t/d+b; };
    from = from || 0;
    to = to || 1;
    framespacing = framespacing || 1;
    
    (function interval() {
        var time = (Date.now() - start);
         if(time < duration) {
            effectFrame(easing(0, time, from, change, duration));
             scrolling = true;
            window.setTimeout(interval, framespacing );
        } else {
            effectFrame(to);
            scrolling = false;
        }
    }());
}
           

window.smoothScrollTo = function (target, duration) {
    var start = window.pageYOffset;        
    duration = duration || 500;
    
    animation(function(position) { window.scroll(0,position); }, duration, start, target);
    
};
movePresentation(0);

function scrollTo(element, to, duration) {
  if (duration < 0) return;
  var difference = to - element.scrollTop;
  var perTick = difference / duration * 10;
scrolling=true;

  setTimeout(function() {
    element.scrollTop = element.scrollTop + perTick;
    if (element.scrollTop == to)
    {
        scrolling=false;
        return;
    }
    scrollTo(element, to, duration - 10);
  }, 10);
    
}

function openMapDropdown()
{
    document.getElementById("dropdown_map").style.transition = "max-height 5s, max-width 5s, opacity 0.3s"
    document.getElementById("drop_item_1").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_2").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_3").style.transition = "font-size 0.3s";
    document.getElementById("dropdown_map").style.opacity = 1;
    document.getElementById("drop_item_1").style.fontSize = "15px";
    document.getElementById("drop_item_2").style.fontSize = "15px";
    document.getElementById("drop_item_3").style.fontSize = "15px";
    document.getElementById("dropdown_map").style.maxWidth = "9999px";
    document.getElementById("dropdown_map").style.maxHeight = "9999px";
}

function closeMapDropdown()
{
    document.getElementById("dropdown_map").style.transition = "max-height 0.3s, max-width 0.3s, opacity 0.3s"
    document.getElementById("drop_item_1").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_2").style.transition = "font-size 0.3s";
    document.getElementById("drop_item_3").style.transition = "font-size 0.3s";
    document.getElementById("dropdown_map").style.opacity = 0;
    document.getElementById("drop_item_1").style.fontSize = "0em";
    document.getElementById("drop_item_2").style.fontSize = "0em";
    document.getElementById("drop_item_3").style.fontSize = "0em";
    document.getElementById("dropdown_map").style.maxWidth = "0px";
    document.getElementById("dropdown_map").style.maxHeight = "0px";
}
