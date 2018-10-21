module.exports = function alreadyInUse (err){

  // Get access to `res`
  // (since the arguments are up to us)
  var res = this.res;

  if (err.invalidAttributes.email) {
    return res.send(409, 'Email address is already taken by another user, please try again.');
  }

  if (err.invalidAttributes.username) {
    return res.send(409, 'Username is already taken by another user, please try again.');
  }

  if(err.invalidAttributes.devid){
    return res.send(409, 'Device ID is already taken by another user, please try again.\n Thiết bị đã được sử dụng bởi khách hàng khác, vui lòng thử lại!');
}
else{
	return res.send(409, err);
}

};
