angular.module('TableTabModule', []).controller('TableTabController', ['$scope', '$http', 'toastr', function($scope, $http, toastr){

console.log("TABLE TableTabController Has Loaded\n");
$scope.data_collect = [
      {
        devid: 1,
        packetid: 1,
        timestamp: new Date().toLocaleString(),
        humid: 50.1,
        temp: 20.1,
        Lat: 10.760092,
        Long: 106.662546,
        locked: true
      }, 
      {
        devid: 2,
        packetid: 2,
        timestamp: new Date().toLocaleString(),
        humid: 50.2,
        temp: 20.2,
        Lat: 10.759554,
        Long: 106.662592,
        locked: true
      },

      {
        devid: 3,
        packetid: 3,
        timestamp: new Date().toLocaleString(),
        humid: 50.3,
        temp: 20.3,
        Lat: 10.758674,
        Long: 106.662737,
        locked: true
      },

      {
        devid: 1,
        packetid: 2,
        timestamp: new Date().toLocaleString(),
        humid: 50.4,
        temp: 20.4,
        Lat: 10.758669,
        Long: 106.662887,
        locked: true
      },

      {
        devid: 5,
        packetid: 5,
        timestamp: new Date().toLocaleString(),
        humid: 50.5,
        temp: 20.5,
        Lat: 10.758804,
        Long: 106.663459,
        locked: true
      },

      {
        devid: 6,
        packetid: 6,
        timestamp: new Date().toLocaleString(),
        humid: 50.6,
        temp: 20.6,
        Lat: 10.75886,
        Long: 106.663767,
        locked: true
      },

      {
        devid: 7,
        packetid: 7,
        timestamp: new Date().toLocaleString(),
        humid: 50.7,
        temp: 20.7,
        Lat: 10.759301,
        Long: 106.663679,
        locked: true
      },
    ]




}]);
// });