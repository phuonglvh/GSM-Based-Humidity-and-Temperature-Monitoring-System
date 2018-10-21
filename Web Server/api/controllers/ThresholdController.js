/**
 * ThresholdController
 *
 * @description :: Server-side actions for handling incoming requests.
 * @help        :: See https://sailsjs.com/docs/concepts/actions
 */

module.exports = {
  GetThresholdList: function(req, res){
	console.log('... entered ThresholdController/GetThresholdList');

  	Threshold.find({owner: req.session.userId}).sort({devid: 'ASC'}).exec(function(err, foundAll){
  		if(err) return res.negotitate(err);
  		if(foundAll.length == 0) return res.notFound();
  		return res.json(200, foundAll);
  	});
  }, /*GetThresholdList*/

  UpdateThreshold: function(req, res){
	console.log('... entered ThresholdController/UpdateThreshold');
	console.log({
  			devid: req.param('devid'),
  			upperTemp: req.param('upperTemp'),
  			lowerTemp: req.param('lowerTemp'),
  			upperHumid: req.param('upperHumid'),
  			lowerHumid: req.param('lowerHumid'),
  	});

  	Threshold.findOne({devid: req.param('devid')}, function(err, foundOne){
  		if(err) return res.negotitate(err);
  		if(!foundOne) {
  			console.log("ThresholdController/UpdateThreshold/" + req.param('devid') + 'not successfully!');
  			return res.notFound();
		}
  		Threshold.update({devid: req.param('devid')}, {
  			upperTemp: req.param('upperTemp'),
  			lowerTemp: req.param('lowerTemp'),
  			upperHumid: req.param('upperHumid'),
  			lowerHumid: req.param('lowerHumid'),
  		}, function(err, updatedOne){
  			if(err) return res.negotitate(err);
  			console.log(updatedOne);
  			return res.ok();
  		}); /*Threshold.update*/
  	}); /*Threshold.findOne*/
  },/*Threshold*/

  RemoveThreshold: function(req, res){
		console.log('... entered ThresholdController/RemoveThreshold/' + req.param('devid'));
	  	Threshold.findOne({devid: req.param('devid'), owner: req.session.userId}, function(err, foundOne){

	  		if(err) return res.negotitate(err);
	  		if(!foundOne) {
	  			console.log("ThresholdController/RemoveThreshold/" + req.param('devid') + 'not successfully!');
	  			return res.notFound();
	  		}//badRequest("Thiết bị được yêu cầu xóa ngưỡng không tồn tại");

	  		Threshold.update({devid: req.param('devid')}, {
	  			upperTemp: 0,
	  			lowerTemp: 0,
	  			upperHumid: 0,
	  			lowerHumid: 0,
	  		}, function(err, updatedOne){
	  			if(err) return res.negotitate(err);
	  			console.log('Removed Threshold of devid: '+  req.param('devid'));
	  			return res.ok();
	  		}); /*Threshold.update*/

  		}); /*Threshold.findOne*/
  },/*RemoveThreshold*/

};

