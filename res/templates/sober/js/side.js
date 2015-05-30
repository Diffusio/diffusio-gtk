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


$(document).ready(function(){
	var side = $('.sideBar');
	var sideWidth = $('.sideBar').width() + 65;
	var sideClose = $('#sideClose');
	side.css({'left' : '-'+sideWidth+'px'});
	var filmWhite = $('.filmWhite');
	var bodyHeight = $('body').height() + 100;
	var bodyWidth = $('body').width() + 40;
	var body = $('body');
	
	var sideOpen = $("#sideOpen");
	var subPage = $(".subPage");
	filmWhite.hide();
	
	sideOpen.click(function(){
    side.css({'left' : '0px', 'transition':'0.5s', '-moz-transition':'0.5s', '-webkit-transition':'0.5s', '-o-transition':'0.5s', '-khtml-transition':'0.5s', '-ms-transition':'0.5s'});
    body.css({'overflow':'hidden'});
    filmWhite.show();
    filmWhite.css({'height':bodyHeight+'px','width':bodyWidth+'px'});
	});
	sideClose.click(function(){
    side.css({'left' : '-'+sideWidth+'px', 'transition':'0.5s', '-moz-transition':'0.5s', '-webkit-transition':'0.5s', '-o-transition':'0.5s', '-khtml-transition':'0.5s', '-ms-transition':'0.5s'});
    body.css({'overflow':'scroll-y'});
    filmWhite.hide();
	});
	subPage.click(function(){
    side.css({'left' : '-'+sideWidth+'px', 'transition':'0.5s', '-moz-transition':'0.5s', '-webkit-transition':'0.5s', '-o-transition':'0.5s', '-khtml-transition':'0.5s', '-ms-transition':'0.5s'});
    body.css({'overflow':'scroll-y'});
    filmWhite.hide();
	});
	filmWhite.click(function(){
    side.css({'left' : '-'+sideWidth+'px', 'transition':'0.5s', '-moz-transition':'0.5s', '-webkit-transition':'0.5s', '-o-transition':'0.5s', '-khtml-transition':'0.5s', '-ms-transition':'0.5s'});
    body.css({'overflow':'scroll-y'});
    filmWhite.hide();
	});
});

