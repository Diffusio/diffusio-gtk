/*
 * Diffusio - Build presentation websites easily
 * Copyright (C) 2015 Pierre JACQUIER - Grégoire DUVAUCHELLE
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
License
 * along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

Array.prototype.shuffle = function() {
  var i = this.length, j, temp;
  if ( i == 0 ) return this;
  while ( --i ) {
     j = Math.floor( Math.random() * ( i + 1 ) );
     temp = this[i];
     this[i] = this[j];
     this[j] = temp;
  }
}

var last_scroll_pos = 0; 
var dS;
var b_wth, b_hgt;
var news = document.getElementsByClassName('news');
var news_l = news.length;
var y=document.getElementById('cover').style.top;
var colors = ["#F44336","#E91E63","#9C27B0","#673AB7","#3F51B5","#2196F3","#009688","#4CAF50","#FF5722","#795548","#607D8B"];
colors.shuffle();
var j=0;
for(var i=0;i<news_l;i++)
{
    news[i].style.background = colors[j];
    if(j>9)
        j = 0;
    else 
        j++;
}

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


function openCircleNews(id)
{
    var i;
    for(i=0;i<news_l;i++)
        if(news[i].id != ('news_' + id))
            news[i].style.transform = 'translateX(-' + document.getElementById('wrapper').offsetWidth + 'px)';
        else
        {
          news[i].style.transform = 'translateY(-' + (news[i].offsetTop ) + 'px)';
            news[i].style.width = '80%';
            news[i].getElementsByClassName('news_content')[0].style.display = 'block';
            news[i].getElementsByClassName('read_more')[0].innerHTML = "CLOSE";
            news[i].getElementsByClassName('read_more')[0].style.color = 'white';
            news[i].getElementsByClassName('read_more')[0].onmousedown = function() {closeCircleNews(id)};
        }
}

function closeCircleNews(id)
{
    var news = document.getElementsByClassName('news');
    var news_l = news.length;
    var i;
    for(i=0;i<news_l;i++)
        if(news[i].id != ('news_' + id))
            news[i].style.transform = 'translateX(0px)';
        else
        {
          news[i].style.transform = 'translateY(0px)';
            news[i].style.width = '300';
            news[i].getElementsByClassName('news_content')[0].style.display = 'none';
            news[i].getElementsByClassName('read_more')[0].innerHTML = "READ MORE";
            news[i].getElementsByClassName('read_more')[0].onmousedown = function() {openCircleNews(id)};
        }
}

function update()  
{
        var icons = document.getElementsByClassName('tab_img');
        var tabs = document.getElementsByClassName('sub_tab');
        getViewport();
        dS = (document.body.scrollTop - last_scroll_pos) * 0.2;
        y=document.getElementById('cover').style.top;
        y = parseInt(y);
        y -= dS;
        document.getElementById('cover').style.top = y;
        document.getElementById('cover').style.top -= parseInt(dS);
    if(document.body.scrollTop >= document.getElementById("content_1").offsetTop - 110 && document.body.scrollTop <= ( document.getElementById("content_2").offsetTop - document.getElementById('header_1').offsetHeight ))
    {
        document.getElementById('header_1').style.display = "block";
    }
    else
    {
        document.getElementById('header_1').style.display = "none";
    }
     if(document.body.scrollTop >= document.getElementById("content_1").offsetTop - 110)
        document.getElementById('h1_tabs').style.display = "block";
    else
        document.getElementById('h1_tabs').style.display = "none";
    if(document.body.scrollTop >= document.getElementById('content_2').offsetTop && document.body.scrollTop >= document.getElementById('content_2').offsetTop)
        document.getElementById('header_2').style.position = 'fixed';
    else
        document.getElementById('header_2').style.position = 'absolute';
    if(document.body.scrollTop > document.getElementById('content_2').offsetTop + document.getElementById('content_2').offsetHeight)
        document.getElementById('header_3').style.position = 'fixed';
    else
        document.getElementById('header_3').style.position = 'absolute';
    last_scroll_pos = document.body.scrollTop;
}

function scrollToTop()
{
    document.body.scrollTop = 0;
    last_scroll_pos = 0;
    document.getElementById('cover').style.top=0;   
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