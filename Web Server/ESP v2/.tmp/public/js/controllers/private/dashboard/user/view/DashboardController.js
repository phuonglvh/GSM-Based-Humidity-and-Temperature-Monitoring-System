angular.module('DashboardModule').controller('DashboardController', ['$location' ,'$scope', '$http', 'toastr', function($location, $scope, $http, toastr){

/*//, '$timeout'
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
      toastr.warning('Đã đăng xuất.', 'Warning', {
          closeButton: true,
          timeOut: 4000 
        });
      window.location = '/';
    })
    .catch (function onError(sailsResponse){
      toastr.error(sailsResponse);
    })
    .finally(function eitherWay(){

    });
 };


$scope.InitChartView = function () {
	$.get('/device/GetDevList', function(getRes, status){
          document.getElementById("SearchChartByDevId").options.length = 0;
					var option = document.createElement("option");
              option.text = "";
              option.value = "";
              document.getElementById("SearchChartByDevId").add(option);
              
            for (var i = 0; i < getRes.length; i++) {
              if(getRes[i].valid){
                var option = document.createElement("option");
                option.text = getRes[i].devid.toString();
                option.value = getRes[i].devid;
                document.getElementById("SearchChartByDevId").add(option);
              }//if
            }//for
        });/*get*/
}; //InitChartView

$scope.InitMonitorView = function () {
  $.get('/device/GetDevList', function(getRes, status){
          if(getRes.length == 0) toastr.error("No data found!\nKhông tìm thấy dữ liệu");
            else toastr.success("Đã cập nhật thiết bị", "Thông báo");

          document.getElementById("SearchMonitorDataByDevId").options.length = 0;
          var option = document.createElement("option");
              option.text = "";
              option.value = "";
              document.getElementById("SearchMonitorDataByDevId").add(option);
              
            for (var i = 0; i < getRes.length; i++) {
              if(getRes[i].valid){
                var option = document.createElement("option");
                option.text = getRes[i].devid.toString();
                option.value = getRes[i].devid;
                document.getElementById("SearchMonitorDataByDevId").add(option);
              }//if
            }//for
        });/*get*/
}; //InitMonitorView


///////////////////////////////////////////////////////
// DEVICE
///////////////////////////////////////////////////////
$scope.GetDevDataByID = function(DevId){
  if(!DevId || DevId == '' || DevId == 'undefined'){
    toastr.warning("Vui lòng chọn mã thiết bị");
    var MonitorTable = $('#MonitorTable').dataTable();
      MonitorTable.fnClearTable();
  }
  else{
    $http.get('/data_collect/GetDevDataByID/' + DevId)
    .then(function onSuccess(sailsResponse){

      var res = [];
        for (var i = 0; i < sailsResponse.data.length; i++) {
          res.push(sailsResponse.data[i]);
        }
        //clear the table for new data
          var MonitorTable = $('#MonitorTable').dataTable();
          MonitorTable.fnClearTable();

          //add new data to table
          if(res.length == 0) toastr.error("No data found!\nKhông tìm thấy dữ liệu");
            else toastr.success("Đã cập nhật dữ liệu!");
          for (var i = 0; i < res.length; i++) {

            // toastr.info(res[i]);

            $('#MonitorTable').dataTable().fnAddData([
              res[i]["devid"],
              res[i]["humid"],
              res[i]["temp"],
              new Date(res[i]["createdAt"]).toLocaleString(),
            ]);
          }       
    })
    .catch (function onError(sailsResponse){
      if(sailsResponse.data.length == 0)
      {
        toastr.info("Không tìm thấy dữ liệu!")
      }
      else{
      toastr.error(sailsResponse.status);
      }
       var MonitorTable = $('#MonitorTable').dataTable();
        MonitorTable.fnClearTable();
    })
    .finally(function eitherWay(){

    });
  } 
}; //GetDevDataByID


$scope.AddDeviceForm = {},
$scope.submitAddDevice = function(){
    $http.post('/device/AddDevice', {
    devid: $scope.AddDeviceForm.devid,
    devname: $scope.AddDeviceForm.devname,
    parameter: $scope.AddDeviceForm.parameter,
    })
    .then(function onSuccess(sailsResponse){
      toastr.success('Thông tin đã được gửi! \n Vui lòng thay đổi trạng thái để sử dụng', "Thông báo");
      $scope.GetDevList();
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 409) {
        toastr.error(sailsResponse.data,  "Lỗi");
      }
    })
    .finally(function eitherWay(){
      $('#AddDeviceDialog').modal('hide');
    });
}; //submitAddDevice



$scope.submitChangValidDevice = function(DevId){
    $http.put('/device/ChangValidDevice', {
      devid: DevId,
    })
    .then(function onSuccess(sailsResponse){
      toastr.success("Thiết bị đã được thay đổi trạng thái: " + DevId, "Thông báo");
      // window.location = '/dashboard';
      $scope.GetDevList();
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 409 || sailsResponse.status == 404) {
      toastr.error(sailsResponse.data, "Lỗi");
      }
    })
    .finally(function eitherWay(){
      $('#ChangeValidDialog').modal('hide');
    });
}; //submitLockDevice


$scope.submitRemoveDevice = function(DevId){
    $http.put('/device/RemoveDevice', {
      devid: DevId,
    })
    .then(function onSuccess(sailsResponse){
      toastr.success("Thiết bị đã được xóa!", "Thông báo");
      $scope.GetDevList();
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 404) {
        toastr.error(sailsResponse.data, "Lỗi");
      }
      else toastr.error(sailsReponse);
    })
    .finally(function eitherWay(){
      $('#RemoveDeviceDialog').modal('hide');
    });
}; //submitRemoveDevice

$scope.GetDevList = function(){
  $http.get('/device/GetDevList')
  .then(function onSuccess(sailsResponse){
      toastr.success("Đã cập nhật danh sách thiết bị!", "Thông báo");

      //clear the table for new data
        var MyDeviceTable = $('#MyDeviceTable').dataTable();
        MyDeviceTable.fnClearTable();

        //add new data to table
        for (var i = 0; i < sailsResponse.data.length; i++) {
          $('#MyDeviceTable').dataTable().fnAddData([
            sailsResponse.data[i]["devid"],
            sailsResponse.data[i]["devname"],
            sailsResponse.data[i]["parameter"],
            sailsResponse.data[i]["valid"],
            new Date(sailsResponse.data[i]["createdAt"]).toLocaleString(),
          ]);
        }//for  
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 404) {
        toastr.error(sailsResponse.data, "Lỗi");
      }
      else toastr.error(sailsReponse);
    })
    .finally(function eitherWay(){
    });

}; //GetDevList


$scope.InitWarningView = function () {
   $http.get('/warning/GetWarningList')
    .then(function onSuccess(sailsResponse){
      toastr.success("Danh sách cảnh báo đã được cập nhật!", "Thông báo");

      //clear the table for new data
      var MyWarningTable = $('#MyWarningTable').dataTable();
      MyWarningTable.fnClearTable();

      //add new data to table
      if(sailsResponse.data.length){
        for (var i = 0; i < sailsResponse.data.length; i++) {
          $('#MyWarningTable').dataTable().fnAddData([
            sailsResponse.data[i]["devid"],
            sailsResponse.data[i]["message"],
            new Date(sailsResponse.data[i]["timestamp"]).toLocaleString(),
          ]);
          if(sailsResponse.data[i]["message"] != ''){
            toastr.warning('Thời điểm: '+ new Date(sailsResponse.data[i]["timestamp"]).toLocaleString() + '\n Thiết bị: ' + sailsResponse.data[i]["devid"] + '\nNội dung: ' + sailsResponse.data[i]["message"], "Cảnh báo", 'trustedHtml');
          }
        }//for  
      }//if
    })
    .catch(function onError(sailsResponse){
      //clear the table for new data
      var MyWarningTable = $('#MyWarningTable').dataTable();
      MyWarningTable.fnClearTable();

      if (sailsResponse.status == 404) {
        toastr.error("Danh sách cảnh báo không có dữ liệu nào!", "Cảnh báo");
      }
      else toastr.error(sailsReponse);
    })
    .finally(function eitherWay(){

        $http.get('/threshold/GetThresholdList')
        .then(function onSuccess(sailsResponse){
          toastr.success("Danh sách ngưỡng đã được cập nhật", "Thông báo");
          
         //clear the table for new data
          var MyThresholdTable = $('#MyThresholdTable').dataTable();
          MyThresholdTable.fnClearTable();

          //add new data to table
          for (var i = 0; i < sailsResponse.data.length; i++) {
            $('#MyThresholdTable').dataTable().fnAddData([
              sailsResponse.data[i]["devid"],
              sailsResponse.data[i]["upperHumid"],
              sailsResponse.data[i]["lowerHumid"],
              sailsResponse.data[i]["upperTemp"],
              sailsResponse.data[i]["lowerTemp"],
            ]);
          }//for  
        })
        .catch(function onError(sailsResponse){
          //clear the table for new data
          var MyThresholdTable = $('#MyThresholdTable').dataTable();
          MyThresholdTable.fnClearTable();

          if (sailsResponse.status == 409) {
            toastr.error(sailsResponse.data, "Lỗi");
          }
          else if(sailsResponse.status == 404){
            toastr.error("Mã thiết bị không có trong danh sách! Vui lòng thử lại!", "Lỗi");
          }
        })
        .finally(function eitherWay(){
          setInterval(function(){$scope.LoopWarning()}, 10000);
          
        });
    });
}; //InitChartView

$scope.UpdateThresholdForm = {},
$scope.submitUpdateThreshold = function(){
    $http.put('/threshold/UpdateThreshold', {
      devid: $scope.UpdateThresholdForm.devid,
      upperTemp: $scope.UpdateThresholdForm.upperTemp,
      lowerTemp: $scope.UpdateThresholdForm.lowerTemp,
      upperHumid: $scope.UpdateThresholdForm.upperHumid,
      lowerHumid: $scope.UpdateThresholdForm.lowerHumid,
    })
    .then(function onSuccess(sailsResponse){
      toastr.success("Đã cập nhật ngưỡng của thiết bị: " + $scope.UpdateThresholdForm.devid);
      $scope.InitWarningView();
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 409) {
        toastr.error(sailsResponse);
      }
      else if(sailsResponse.status == 404){
        toastr.error("Mã thiết bị không có trong danh sách! Vui lòng thử lại!", "Lỗi");
      }
    })
    .finally(function eitherWay(){
      $('#UpdateThresholdDialog').modal('hide');

    });
}; //submitUpdateThreshold


$scope.submitRemoveThreshold = function(DevId){
    // console.log('submitRemoveThreshold');
    $http.put('/threshold/RemoveThreshold', {
      devid: DevId,
    })
    .then(function onSuccess(sailsResponse){
      toastr.success("Đã xóa ngưỡng của thiết bị: " + DevId);
      $scope.InitWarningView();
    })
    .catch(function onError(sailsResponse){
      if (sailsResponse.status == 409) {
        toastr.error(sailsResponse.data);
      }
      else if(sailsResponse.status == 404){
        toastr.error("Mã thiết bị không có trong danh sách! Vui lòng thử lại!", "Lỗi");
      }
    })
    .finally(function eitherWay(){
      $('#RemoveThresholdDialog').modal('hide');
    });
}; //submitRemoveThreshold


/*Interval loop for warning table*/
$scope.LoopWarning = function(){
  console.log('LoopWarning');
  $http.get('/warning/GetWarningList')
    .then(function onSuccess(sailsResponse){
      // toastr.success("Danh sách cảnh báo đã được cập nhật!", "Thông báo");

      //clear the table for new data
      var MyWarningTable = $('#MyWarningTable').dataTable();
      MyWarningTable.fnClearTable();

      //add new data to table
      if(sailsResponse.data.length){
        for (var i = 0; i < sailsResponse.data.length; i++) {
          $('#MyWarningTable').dataTable().fnAddData([
            sailsResponse.data[i]["devid"],
            sailsResponse.data[i]["message"],
            new Date(sailsResponse.data[i]["timestamp"]).toLocaleString(),
          ]);        
        }//for  
        // if(sailsResponse.data[sailsResponse.data.length-1]["message"] != ''){
        //     toastr.warning('Thời điểm: '+ new Date(sailsResponse.data[i]["timestamp"]).toLocaleString() + '\n Thiết bị: ' + sailsResponse.data[i]["devid"] + '\nNội dung: ' + sailsResponse.data[i]["message"], "Cảnh báo", 'trustedHtml');
        // }
      }//if
    })
    .catch(function onError(sailsResponse){
      //clear the table for new data
      var MyWarningTable = $('#MyWarningTable').dataTable();
      MyWarningTable.fnClearTable();

      if (sailsResponse.status == 404) {
        toastr.error("Danh sách cảnh báo không có dữ liệu nào!", "Cảnh báo");
      }
      else toastr.error(sailsReponse);
    })
    .finally(function eitherWay(){

    });
};

}]);// angular.controller








