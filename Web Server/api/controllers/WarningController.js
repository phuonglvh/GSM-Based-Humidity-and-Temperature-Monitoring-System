/**
 * WarningController
 *
 * @description :: Server-side actions for handling incoming requests.
 * @help        :: See https://sailsjs.com/docs/concepts/actions
 */

module.exports = {
	GetWarningList: function(req, res){
		console.log('... entered WarningController/GetWarningList');
	  	Warning.find().sort({devid: 'ASC'}).exec(function(err, foundAll){
	  		if(err) return res.negotitate(err);
	  		if(foundAll.length == 0) return res.notFound();
	  		return res.json(200, foundAll);
	  	});
  	}, /*GetWarningList*/
};

