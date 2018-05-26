/**
 * Data_collectController
 *
 * @description :: Server-side logic for managing data_collects
 * @help        :: See http://sailsjs.org/#!/documentation/concepts/Controllers
 */
var isFloat = require('is-float');
var isInt = require('is-int');
var parseDecimalNumber = require('parse-decimal-number');
var async = require('async');


module.exports = {

  GetDevDataByID: function(req, res){
    console.log('... entered Data_collectController/GetDevDataByID/' + req.param('DevId'));
    /*check if logged in*/
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
        console.log('Admin must meet user privacy\n');
        return res.forbidden("Admin must meet user privacy");
      }

      Device.findOne({devid: req.param('DevId'), valid: true}, function(err, foundDev){
        if(err) return res.negotiate(err);
        if(!foundDev) return res.notFound();//"No valid devices matches found!\nThiết bị bạn tìm kiếm không có hiệu lực, vui lòng kích hoạt thiết bị trước!"
      });

      Data_collect.find({devid: req.param('DevId')}).sort({packetid: 'ASC'}).exec(function(err, foundDevById) {
        if (err) return res.negotiate(err);
        if (foundDevById.length === 0) return res.notFound();
        // console.log(JSON.stringify(foundDevById));
        return res.json(foundDevById);
      });//Data_collect.find
    });//User.findOne

  },//GetDevDataByID


  collectData: function(req, res){ //POST/GET
    console.log("... entered Data_collectController.collectData/" + req.param('devid') +'/' + req.param('packetid'));
    Device.findOne({devid: req.param('devid'), valid: true}, function(err, foundOne){
      if(err) return res.negotiate(err);
      if(!foundOne) return res.badRequest('Device not valid!');
       Data_collect.findOne({
          devid: req.param('devid'),
          packetid: req.param('packetid'),
        }).exec(function (err, existingPacketId){
          if (err) 
          {
            console.log(err);
            return res.negotiate(err);
          }
          if (existingPacketId) 
          {
            return res.created("Record already saved!");    
           }

          //
          // valid packetid
          //
          var validData = {};
            validData.devid = req.param('devid');
            validData.packetid = req.param('packetid');
            validData.humid = req.param('curr_Humid');
            validData.temp = req.param('curr_Temp');

            Threshold.findOne({devid: validData.devid},  function(err, foundOne){
              if(!foundOne){}
              else if(!foundOne.upperHumid && !foundOne.lowerHumid && !foundOne.upperTemp && !foundOne.lowerTemp){
              }//else if
              else {
                if(validData.humid > foundOne.upperHumid){
                  Warning.create({
                    devid: validData.devid,
                    packetid: validData.packetid,
                    timestamp: new Date().toLocaleString(),
                    message: 'Vượt quá ngưỡng độ ẩm lớn nhất',
                  }, function(err, createdRecord){
                    console.log(JSON.stringify(createdRecord));
                    if(err) return res.negotiate(err);
                  });
                }

                if(validData.humid < foundOne.lowerHumid){
                  Warning.create({
                    devid: validData.devid,
                    packetid: validData.packetid,
                    timestamp: new Date().toLocaleString(),
                    message: 'Vượt quá ngưỡng độ ẩm thấp nhất',
                  }, function(err, createdRecord){
                    console.log(JSON.stringify(createdRecord));
                    if(err) return res.negotiate(err);
                  });
                }

                if(validData.temp > foundOne.upperTemp){ //
                  Warning.create({
                    devid: validData.devid,
                    packetid: validData.packetid,
                    timestamp: new Date().toLocaleString(),
                    message: 'Vượt quá ngưỡng nhiệt độ lớn nhất',
                  }, function(err, createdRecord){
                    console.log(JSON.stringify(createdRecord));
                    if(err) return res.negotiate(err);
                  });
                }

                if(validData.temp < foundOne.lowerTemp){ //
                  Warning.create({
                    devid: validData.devid,
                    packetid: validData.packetid,
                    timestamp: new Date().toLocaleString(),
                    message: 'Vượt quá ngưỡng nhiệt độ thấp nhất',
                  }, function(err, createdRecord){
                    console.log(JSON.stringify(createdRecord));
                    if(err) return res.negotiate(err);
                  });
                }//if
              }//else
            }); /*Threshold.findOne*/

          Data_collect.create(validData).exec(function(err, createdRecord) {
            if (err) {
              console.log('Data_collect.create error is: ', err.invalidAttributes);
              return res.negotiate(err);
            }//if
            console.log(JSON.stringify(createdRecord));

            Threshold.findOne({devid: validData.devid}, function(err, foundOne){
              if(err) return res.negotiate(err);
              if (!foundOne) {
                return res.json(200, {
                  okID: createdRecord.packetid,
                  upperTemp: 0,
                  lowerTemp: 0,
                  upperHumid: 0,
                  lowerHumid: 0,
                }); //json
              }//if
              else{
                return res.json(200, {
                  okID: createdRecord.packetid,
                  upperTemp: foundOne.upperTemp,
                  lowerTemp: foundOne.lowerTemp,
                  upperHumid: foundOne.upperHumid,
                  lowerHumid: foundOne.lowerHumid,
                }); //json
              }
            }); /*Threshold.findOne*/
          }); //Data_collect.create
      }); //Data_collect.findOne
    }); /*Device.findOne*/
   


    /*console.log(JSON.stringify(req.headers));
    console.log(req.param('devid'));
    console.log(req.param('packetid'));
    console.log(req.param('curr_Humid'));
    console.log(req.param('curr_Temp'));
    return res.json(200, {
      devid: req.param('devid'),
      packetid: req.param('packetid'),
      curr_Humid: req.param('curr_Humid'),
      curr_Temp: req.param('curr_Temp'),
    });*/
  }, //collectData

};


