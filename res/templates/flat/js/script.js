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

//Variables
var news = document.getElementsByClassName("news");
var news_l = news.length;
var b_hgt,b_wth,last_wth = b_wth,size_down;

//Initialisation
update();


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

function update()
{
    getViewport();
    size_down = last_wth > b_wth ? true : false;
    var section_wth = document.getElementById("content_1").offsetWidth;
    document.getElementById("w_d_1").style.marginRight = 6;
    document.getElementById("w_d_1").style.width = section_wth/2 - 26;
    document.getElementById("w_d_2").style.width = section_wth/2 - 26;
    uniformizeHeights();
    last_wth = b_wth;
}

function openCircleNews(id)
{
    document.getElementById("news_title_opened").innerHTML = document.getElementById("news_title_" + id).innerHTML;
    document.getElementById("news_datetime_opened").innerHTML = document.getElementById("news_datetime_" + id).innerHTML;
    document.getElementById("news_content_opened").innerHTML = document.getElementById("news_content_" + id).innerHTML;
    document.body.scrollTop = 0;
    document.getElementById("news_opened").style.top = 0;
    document.getElementById("shadow_news").style.zIndex = 11;
   document.getElementById("shadow_news").style.opacity = 0.8; 
    document.getElementById("close_news").style.display = "block"; 
 
}

function closeCircleNews()
{
    document.body.scrollTop = document.getElementById("content_2").offsetTop;
    document.getElementById("news_opened").style.top = -3000;
    document.getElementById("shadow_news").style.zIndex = -11;
   document.getElementById("shadow_news").style.opacity = 0; 
    document.getElementById("close_news").style.display = "none"; 
 
}

function uniformizeHeights()
{
    var i,max=0,max_p=0;
    for(i=0;i<news_l;i++)
        if(document.getElementById("news_" + (i+1)).offsetHeight > max)
            max = document.getElementById("news_" + (i+1)).offsetHeight;
    for(i=0;i<news_l;i++)
        if(size_down)
            document.getElementById("news_" + (i+1)).style.minHeight = max;
        else
            document.getElementById("news_" + (i+1)).style.minHeight = "none";
    max_p = Math.max(document.getElementById("w_d_1").offsetHeight, document.getElementById("w_d_2").offsetHeight);
     document.getElementById("w_d_1").style.minHeight = max_p;
        document.getElementById("w_d_2").style.minHeight = max_p;
    

}