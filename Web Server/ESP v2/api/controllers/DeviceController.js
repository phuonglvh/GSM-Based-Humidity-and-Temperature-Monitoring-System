/**
 * DeviceController
 *
 * @description :: Server-side logic for managing devices
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */

module.exports = {
	GetDevList: function(req, res) {
		console.log( '... enter DeviceController/GetDevList\n');

		if (!req.session.userId || req.session.userId == 'undefined') {
	      return res.view('homepage', {
	        me: null
	      });
	    }

	    User.findOne({id: req.session.userId}, function(err, foundUser) {
	      if (err) {
	          return res.negotiate(err);
	      }//if(err)

	      /*session of another user*/
	      if (!foundUser) {
	        sails.log.verbose('Session refers to a user who no longer exists- did you delete a user, then try to refresh the page with an open tab logged-in as that user?');
	        return res.view('homepage', {   
	            me: null
	        });
	      }//if
			      
		     if(!foundUser.admin){
		      	var criteria={};
		        criteria.owner = req.session.userId;
		     	Device.find(criteria).sort({devid: 'ASC'}).exec(function (err, foundAll){
		          return res.json(foundAll);
		        });//Device.find()
		  	 }
	     	 else{
	      		return res.badRequest("wrong request!");
		    }//else
	  	});//User.findOne

	},//GetDevList


	ChangValidDevice: function(req, res) {
	   if (!req.session.userId || req.session.userId == 'undefined') {
	        return res.view('homepage', {
	          me: null
	        });
	      }

	      User.findOne(req.session.userId, function(err, foundUser) {
	        if (err) {
	            return res.negotiate(err);
	        }//if(err)

	        /*session of another user*/
	        if (!foundUser) {
	          sails.log.verbose('Session refers to a user who no longer exists- did you delete a user, then try to refresh the page with an open tab logged-in as that user?');
	          return res.view('homepage', {   
	              me: null
	          });
	        }//if
	        if(foundUser.admin){
	          return res.badRequest("No authority to access database");
	        }
	        else if(!foundUser.admin){
	        	Device.findOne({devid: req.param('devid'), owner: req.session.userId}, function(err, foundOne){
	        		if(err){
	        			return res.negotiate(err);
	        		}

	        		if(!foundOne) return res.notFound("Device does not exists/thiết bị không tồn tại");

	        		 Device.update({devid: req.param('devid'), valid: foundOne.valid}, {
		              valid: !foundOne.valid
		              }).exec(function(err, update) {

		              if (err) return res.negotiate(err);
		              return res.ok();
		            });//Device.update
	        	});/*Device.findOne*/

	        }//else if(foundUser.admin)

	      });//User.findOne
	},/*ChangValidDevice*/



	RemoveDevice: function(req, res) {
	   if (!req.session.userId || req.session.userId == 'undefined') {
	        return res.view('homepage', {
	          me: null
	        });
	      }

	      User.findOne(req.session.userId, function(err, foundUser) {
	        if (err) {
	            return res.negotiate(err);
	        }//if(err)

	        /*session of another user*/
	        if (!foundUser) {
	          sails.log.verbose('Session refers to a user who no longer exists- did you delete a user, then try to refresh the page with an open tab logged-in as that user?');
	          return res.view('homepage', {   
	              me: null
	          });
	        }//if
	        if(foundUser.admin){
	          return res.badRequest("No authority to access database");
	        }
	        else if(!foundUser.admin){
	        	Device.findOne({devid: req.param('devid'), owner: req.session.userId}, function(err, foundOne){
	        		if(err) return res.negotiate(err);
	        		if(!foundOne) res.notFound("Device does not exists/thiết bị không tồn tại!");

		        	Device.destroy({devid: req.param('devid')}, function(err, foundOne){
		        		if(err){
		        			return res.negotiate(err);
		        		}
		        		return res.ok();
		        	});/*Device.destroy*/
		        });/*Device.findOne*/
	        }//else if(foundUser.admin)
	      });//User.findOne
	},/*RemoveDevice*/

	AddDevice: function(req, res){
		console.log( '... enter DeviceController/AddDevice/' + req.param('devid'));

		var DeviceInfo = {};
		DeviceInfo.devid = +req.param('devid');
		DeviceInfo.devname = req.param('devname');
		DeviceInfo.parameter = req.param('parameter');
		DeviceInfo.owner = req.session.userId;
		
		User.findOne({id: req.session.userId}, function(err, foundUser){
			if(err) return res.negotiate(err);
			if(!foundUser){
				sails.log.verbose('Session refers to a user who no longer exists- did you delete a user, then try to refresh the page with an open tab logged-in as that user?');
	          return res.view('homepage', {   
	              me: null
	          });
			}

			Device.create(DeviceInfo).exec(function(err, createdDevice) {
	          if (err) {
	            // Check for duplicate devid
	            if (err.invalidAttributes && err.invalidAttributes.devid && err.invalidAttributes.devid[0] && err.invalidAttributes.devid[0].rule === 'unique') {
	            	console.log(err);
	              return res.alreadyInUse(err);
	            }
	            // Check for duplicate devname
	            if (err.invalidAttributes && err.invalidAttributes.devname && err.invalidAttributes.devname[0] && err.invalidAttributes.username[0].rule === 'unique') {
	            	console.log(err);
	              return res.alreadyInUse(err);
	            }
	            return res.negotiate(err);
	          }

	          //debug
	          console.log('> Device: '+req.param('devid')+ ' added\n');
	          return res.json({
	            devid: createdDevice.devid
	          }); //res.json
	        }); //Device.create
		}); /* User.findOne */
	},


};

