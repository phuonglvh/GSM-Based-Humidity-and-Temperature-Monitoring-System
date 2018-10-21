angular.module('DashboardModule').controller('DashboardController', ['$location' ,'$scope', '$http', 'toastr', function($location, $scope, $http, toastr){

/*
   ____          _____                _           
  / __ \        |  __ \              | |          
 | |  | |_ __   | |__) |___ _ __   __| | ___ _ __ 
 | |  | | '_ \  |  _  // _ \ '_ \ / _` |/ _ \ '__|
 | |__| | | | | | | \ \  __/ | | | (_| |  __/ |   
  \____/|_| |_| |_|  \_\___|_| |_|\__,_|\___|_|                                                                                                  

*/
$scope.me = window.SAILS_LOCALS.me;

/*  _____   ____  __  __   ______               _       
 |  __ \ / __ \|  \/  | |  ____|             | |      
 | |  | | |  | | \  / | | |____   _____ _ __ | |_ ___ 
 | |  | | |  | | |\/| | |  __\ \ / / _ \ '_ \| __/ __|
 | |__| | |__| | |  | | | |___\ V /  __/ | | | |_\__ \
 |_____/ \____/|_|  |_| |______\_/ \___|_| |_|\__|___/
*/
$scope.logout = function() {
    $http.post('/logout')
    .then(function onSuccess(sailsReponse){

      window.location = '/';

    })
    .catch (function onError(sailsResponse){
      console.error(sailsResponse);
    })
    .finally(function eitherWay(){

    });
 };


///////////////////////////////////////////////////////
// SERVICE
///////////////////////////////////////////////////////
$scope.serviceList = [];
$scope.GetServiceList = function(){
  $http.get('/service/GetServiceList').success(function(res) {
    //
    //debug
    //
    console.log(res);
    console.log('\n\nservice length is:' +res.length);

        //clear the table for new data
        var dataTable1 = $('#ServiceListTable').dataTable();
        dataTable1.fnClearTable();

        //add new data to table
        for (var i = 0; i < res.length; i++) {
          $scope.serviceList.push(res[i]);
          // console.log('$scope.serviceList ' + i + ' : ' + $scope.serviceList);

          if(!$scope.me.admin){
            $('#ServiceListTable').dataTable().fnAddData([
              res[i]["id"],
              res[i]["devid"],
              res[i]["devname"],
              res[i]["parameter"],
              res[i]["renter"],
              res[i]["valid"],
              res[i]["dep_Lat"],
              res[i]["dep_Long"],
              res[i]["des_Lat"],
              res[i]["des_Long"],
              res[i]["note"],
              new Date(res[i]["createdAt"]).toLocaleString(),
              new Date(res[i]["updatedAt"]).toLocaleString(),
            ]);
          }
        }       
        
  });
}; //GetServiceList

$scope.AdminUpdateValid = function(id, change){
  $http.put('/service/AdminUpdateValid', {
        id: id,
        valid: change,
      })
      .then(function onSuccess(sailsResponse) {
        // toastr.success('user record saved!','', { timeOut: 1000 });
        var x = document.getElementById("snackbar");
        x.className = "show";
        x.innerHTML = "record saved!";
        setTimeout(function(){ x.className = x.className.replace("show", ""); x.innerHTML = "";}, 3000);
      })
      .catch(function onError(sailsResponse) {
        toastr.success('An unexpected error occurred: '+ (sailsResponse.data || sailsResponse.status),'', { timeOut: 1000 });
        // $scope.editProfile.errorMsg = 'An unexpected error occurred: ' + (sailsResponse.data || sailsResponse.status);
      })
      .finally(function eitherWay() {
        // $scope.userList.loading = false;
        console.log('AdminUpdateValid/finally')

      });
};//AdminUpdateValid

$scope.GetHistoryList = function(){
  $http.get('/service/GetHistoryList').success(function(res) {
    console.log('length: ' + res.length + ' : ' + res);

        //clear the table for new data
        var dataTable1 = $('#HistoryListTable').dataTable();
        dataTable1.fnClearTable();

        //add new data to table
        for (var i = 0; i < res.length; i++) {
          $('#HistoryListTable').dataTable().fnAddData([
          res[i]["id"],
          res[i]["devid"],
          res[i]["devname"],
          res[i]["renter"],
          res[i]["valid"],
          new Date(res[i]["createdAt"]).toLocaleString(),
          new Date(res[i]["updatedAt"]).toLocaleString(),
          res[i]["dep_Lat"],
          res[i]["dep_Long"],
          res[i]["des_Lat"],
          res[i]["des_Long"],
          res[i]["note"],
          ]);
        }//for  
  });
}; //GetHistoryList

$scope.GetHistoryListByRenter_Email_ID = function(Email_ID){
  $http.post('/service/GetHistoryListByRenter_Email_ID/', 
    {
      email: Email_ID,
      username: Email_ID,
      id: Email_ID,
    }).success(function(serviceList) {
    console.log('length: ' + serviceList.length + ' : ' + serviceList);

    // var serviceList = serviceList;
    $http.get('/device/GetDevInfoByDevId/' + serviceList[0]["devid"]).success(function(res) {

      //clear the table for new data
        var dataTable1 = $('#HistoryListTable').dataTable();
        dataTable1.fnClearTable();

        //add new data to table
        for (var i = 0; i < serviceList.length; i++) {
          $('#HistoryListTable').dataTable().fnAddData([
          serviceList[i]["id"],
          serviceList[i]["devid"],
          res.devname,
          serviceList[i]["renter"],
          serviceList[i]["valid"],
          new Date(serviceList[i]["createdAt"]).toLocaleString(),
          new Date(serviceList[i]["updatedAt"]).toLocaleString(),
          serviceList[i]["dep_Lat"],
          serviceList[i]["dep_Long"],
          serviceList[i]["des_Lat"],
          serviceList[i]["des_Long"],
          serviceList[i]["note"],
          ]);
        }//for  

    });
        
  });
}; //GetHistoryList

$scope.GetHistoryListByDevID = function(DevId){
  $http.get('/service/GetHistoryListByDevID/'+ DevId).success(function(res) {
    console.log('length: ' + res.length + ' : ' + res);

        //clear the table for new data
        var dataTable1 = $('#HistoryListTable').dataTable();
        dataTable1.fnClearTable();

        //add new data to table
        for (var i = 0; i < res.length; i++) {
          $('#HistoryListTable').dataTable().fnAddData([
          res[i]["id"],
          res[i]["devid"],
          res[i]["devname"],
          res[i]["renter"],
          res[i]["valid"],
          new Date(res[i]["createdAt"]).toLocaleString(),
          new Date(res[i]["updatedAt"]).toLocaleString(),
          res[i]["dep_Lat"],
          res[i]["dep_Long"],
          res[i]["des_Lat"],
          res[i]["des_Long"],
          res[i]["note"],
          ]);
        }//for  
  });
}; //GetHistoryList

$scope.AddServiceForm = {},
$scope.SumitAddService = function(){
    $http.post('/service/AddService', {
      devid: $scope.AddServiceForm.devid,
      RenterEmail: $scope.AddServiceForm.RenterEmail,
      dep_Lat: $scope.AddServiceForm.dep_Lat,
      dep_Long: $scope.AddServiceForm.dep_Long,
      des_Lat: $scope.AddServiceForm.des_Lat,
      des_Long: $scope.AddServiceForm.des_Long,
      note: $scope.AddServiceForm.note,
    })
    .then(function onSuccess(sailsResponse){
      window.location = '/dashboard';
    })
    .catch(function onError(sailsResponse){
    if (sailsResponse.status == 409) {
      toastr.error(sailsResponse.data);
      return;
    }
    // $scope.signupForm.errorMsg = 'An unexpected error occurred: ' + (sailsResponse.data || sailsResponse.status);
    })
    .finally(function eitherWay(){
      $scope.AddServiceForm.loading = false;
    });//finally
}; //SumitAddService


///////////////////////////////////////////////////////
// DEVICE
///////////////////////////////////////////////////////
$scope.GetDevDataByID = function(DevId){
  if(!DevId || DevId ==""){
    var dataTable1 = $('#dataTable1').dataTable();
      dataTable1.fnClearTable();
  }
  else{
    $http.get('/data_collect/GetDevDataByID/' + DevId).success(function(res) {
      // console.log(res + ' : ' + res.length);
          //clear the table for new data
          var dataTable1 = $('#dataTable1').dataTable();
          dataTable1.fnClearTable();

          //add new data to table
          for (var i = 0; i < res.length; i++) {
            $('#dataTable1').dataTable().fnAddData([
            res[i]["devid"],
            // res[i]["devname"],
            res[i]["packetid"],
            res[i]["humid"],
            res[i]["temp"],
            res[i]["Lat"],
            res[i]["Long"],
            res[i]["locked"],
            res[i]["timestamp"],
            // new Date().setTime(res[i]["timestamp"]).toLocaleString(),
            new Date(res[i]["createdAt"]).toLocaleString(),
            ]);
          }       
    });
  }
}; //GetDevDataByID

$scope.GetDevList = function(){
  $http.get('/device/GetDevList').success(function(res) {
    // console.log(res);
    // console.log('\n\nlength is:' +res.length);

        //clear the table for new data
        var dataTable1 = $('#DeviceListTable').dataTable();
        dataTable1.fnClearTable();

        //add new data to table
        for (var i = 0; i < res.length; i++) {
          $('#DeviceListTable').dataTable().fnAddData([
          res[i]["devid"],
          res[i]["devname"],
          res[i]["parameter"],
          new Date(res[i]["createdAt"]).toLocaleString(),
          ]);
        }//for  
  });
}; //GetDevList


$scope.AddDeviceForm = {},
$scope.submitAddDevice = function(){
    $http.post('/device/AddDevice', {
    devid: $scope.AddDeviceForm.devid,
    devname: $scope.AddDeviceForm.devname,
    parameter: $scope.AddDeviceForm.parameter,
    })
    .then(function onSuccess(sailsResponse){
      window.location = '/dashboard';
    })
    .catch(function onError(sailsResponse){
    if (sailsResponse.status == 409) {
      toastr.error(sailsResponse.data);
      return;
    }
    $scope.AddDeviceForm.errorMsg = 'An unexpected error occurred: ' + (sailsResponse.data || sailsResponse.status);
    })
    .finally(function eitherWay(){
      GetDevList();
    });
}; //submitAddDevice


///////////////////////////////////////////////////////
// CHART
///////////////////////////////////////////////////////





}]);// angular.controller







