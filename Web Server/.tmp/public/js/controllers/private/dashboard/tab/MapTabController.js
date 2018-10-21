angular.module('MapTabModule').controller('MapTabController', ['$location' ,'$scope', '$http', 'toastr', function($location, $scope, $http, toastr){

/*
   ____          _____                _           
  / __ \        |  __ \              | |          
 | |  | |_ __   | |__) |___ _ __   __| | ___ _ __ 
 | |  | | '_ \  |  _  // _ \ '_ \ / _` |/ _ \ '__|
 | |__| | | | | | | \ \  __/ | | | (_| |  __/ |   
  \____/|_| |_| |_|  \_\___|_| |_|\__,_|\___|_|                                                                                                  

*/

/*M E - D I C T I O N A R Y*/
$scope.me = window.SAILS_LOCALS.me;
// $scope.TrackingCoordinates = [
//           {lat: 10.746994, lng: 106.676301},
//           {lat: 10.74634, lng: 106.674778},
//           {lat: 10.745644, lng: 106.672847},
//           {lat: 10.746524, lng: 106.672745},
//           {lat: 10.746978, lng: 106.6726},
//           {lat: 10.74688, lng: 106.672173},
//         ];

/*  _____   ____  __  __   ______               _       
 |  __ \ / __ \|  \/  | |  ____|             | |      
 | |  | | |  | | \  / | | |____   _____ _ __ | |_ ___ 
 | |  | | |  | | |\/| | |  __\ \ / / _ \ '_ \| __/ __|
 | |__| | |__| | |  | | | |___\ V /  __/ | | | |_\__ \
 |_____/ \____/|_|  |_| |______\_/ \___|_| |_|\__|___/
*/

/*LOGOUT ACTION*/
$scope.logout = function() {
    $http.post('/user/logout')
    .then(function onSuccess(sailsReponse){

      window.location = '/';

    })
    .catch (function onError(sailsResponse){
      console.error(sailsResponse);
    })
    .finally(function eitherWay(){

    });
 };

// $scope.initMap = function() {
//         var map = new google.maps.Map(document.getElementById('map'), {
//           zoom: 17,
//           center: {lat: 10.746994, lng: 106.676301},
//           mapTypeId: 'terrain'
//         });

//         var TrackingCoordinates = [
//           {lat: 10.746994, lng: 106.676301},
//           {lat: 10.74634, lng: 106.674778},
//           {lat: 10.745644, lng: 106.672847},
//           {lat: 10.746524, lng: 106.672745},
//           {lat: 10.746978, lng: 106.6726},
//           {lat: 10.74688, lng: 106.672173},
//         ];

//         console.log(TrackingCoordinates);

//         var flightPath = new google.maps.Polyline({
//           path: TrackingCoordinates,
//           geodesic: true,
//           strokeColor: '#FF0000',
//           strokeOpacity: 1.0,
//           strokeWeight: 4
//         });

//         flightPath.setMap(map);
//   };




}]);



