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
*/

var desktop = false;
function toogleMobile()
{
	var wth = desktop ? "70%" : "400px";
	var hgt = desktop ? "600px" : "600px";
	var icon = desktop ? 
"images/smartphone.png" : "images/laptop.png";
	var help_FAB = desktop ? "Switch to Mobile view" : "Switch to Desktop view";

	for (i = 1; i < 5; i++) 
		{
			
document.getElementById('frame_' + i).style.width = wth;
			
document.getElementById('frame_' + i).style.height = hgt;
		}
		desktop = !desktop;			
	document.getElementById('smartp').src = 
icon;
	
document.getElementById('help_FAB_content').innerHTML = help_FAB;
}
