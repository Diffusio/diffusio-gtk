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
var geocoder;
var map;
var address = "rue neuve conliege";
var mapOptions = {
  zoom: 17,
  mapTypeId: google.maps.MapTypeId.ROADMAP
}
var marker;

//Init
function initialize() {
    geocoder = new google.maps.Geocoder();
    map = new google.maps.Map(document.getElementById('map_canvas'), mapOptions);
    codeAddress();
}

//Functions
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

      } else {
        alert('Geocode was not successful for the following reason: ' + status);
      }
    });
}