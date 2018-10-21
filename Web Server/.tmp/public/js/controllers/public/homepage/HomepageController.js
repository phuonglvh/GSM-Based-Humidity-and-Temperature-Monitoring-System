angular.module('HomepageModule').controller('HomepageController', ['$scope', '$http', 'toastr', function($scope, $http, toastr){

	$scope.loginForm = {
		loading: false
	}

	$scope.submitLoginForm = function (){
    $scope.loginForm.loading = true;

    $http.put('/user/login', {
      email: $scope.loginForm.email_username,
      username: $scope.loginForm.email_username,
      password: $scope.loginForm.password
    })
    .then(function onSuccess (){
      // Refresh the page now that we've been logged in.
      toastr.success("Logged in successfully", 'Success', {
          closeButton: true,
          timeOut: 4000 
        });
      window.location = '/dashboard';
    })
    .catch(function onError(sailsResponse) {

      // Invalid username / password combination.
      if (sailsResponse.status === 400 || 404) {
        toastr.error('Invalid email/password combination.', 'Error', {
          closeButton: true,
          timeOut: 2000 
        });
        return;
      }
				toastr.error('An unexpected error occurred, please try again.', 'Error', {
					closeButton: true,
					timeOut: 2000 
				});
				return;
    })
    .finally(function eitherWay(){
      $scope.loginForm.loading = false;
    });
  };


}]);
