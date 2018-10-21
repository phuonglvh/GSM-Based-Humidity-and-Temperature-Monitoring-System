/**
 * Bootstrap
 * (sails.config.bootstrap)
 *
 * An asynchronous bootstrap function that runs before your Sails app gets lifted.
 * This gives you an opportunity to set up your data model, run jobs, or perform some special logic.
 *
 * For more information on bootstrapping your app, check out:
 * http://sailsjs.org/#!/documentation/reference/sails.config/sails.config.bootstrap.html
 */

module.exports.bootstrap = function(cb) {
  const os = require('os');
  var async = require('async');
  var Passwords = require('machinepack-passwords');
  var Gravatar = require('machinepack-gravatar');
  var request = require('request');


  /*FAKE USER*/
  var BOOTSTRAP_USER = [
    {
      id: 1,
      email: 'hoangphuongle1997@gmail.com',
      username: 'hoangphuongle1997',
      password: '123456',
      admin: true,
      company: 'BKU',
      gravatarURL: 'https://www.musictalentindia.com/upload/default.png',
      address: '268 LTK, District 10, HCMC, Vietnam',
      phone: 0981908904
    }, 
    {
      id: 2,
      email: 'phuonglevanhoangbk@gmail.com',
      username: 'phuonglevanhoangbk',
      password: '123456',
      admin: true,
      company: 'BKU',
      gravatarURL: 'https://www.musictalentindia.com/upload/default.png',
      address: '268 LTK, District 10, HCMC, Vietnam',
      phone: 0981908904
    },

    {
      id: 3,
      email: 'anonymous@gmail.com',
      username: 'anonymous',
      password: '123456',
      admin: false,
      company: 'hp company',
      gravatarURL: 'http://1.bp.blogspot.com/-aK4ZmDm6-Ic/VCKCugXazRI/AAAAAAAAAKU/r5o_5-XNXtQ/s1600/Sp.png',
      address: '268 LTK, District 10, HCMC, Vietnam',
      phone: 0981908904
    }
  ];
  async.each(BOOTSTRAP_USER, function findOrCreateEachFakeUser(fakeUser, next){
    User.findOne({
      email: fakeUser.email
    }).exec(function (err, existingUser){
      if (err) return next(err);
      if (existingUser) {
        return next();
      }
      Passwords.encryptPassword({
        password: fakeUser.password,
      }).exec({
        error: function(err) {
          return next(err);
        },
        success: function(encryptedPassword) {
          // Get the gravatar url for the fakeUser
          var gravatarURL;
          try {
            gravatarURL = Gravatar.getImageUrl({
              emailAddress: fakeUser.email
            }).execSync();

          } catch (err) {
            return next(err);
          }

          // Create a new user record with various stuff we just built
          User.create({
            id: fakeUser.id,
            gravatarURL: fakeUser.gravatarURL,
            encryptedPassword: encryptedPassword,
            email: fakeUser.email,
            username: fakeUser.username,
            deleted: false,
            admin: fakeUser.admin,
            banned: false,
            company: fakeUser.company,
            address: fakeUser.address,
            phone: fakeUser.phone
          }).exec(function(err, createdUser) {
            if (err) {
              return next(err);
            }
            return next();
          }); //</User.create()>
        }
      }); //</Passwords.encryptPassword>
    }); // </ User.find
  }, function afterwards(err){
    if (err) {
      return cb(err);
    }

    //BOOTSTRAP DATA_COLLECT
    var BOOTSTRAP_DATA_COLLECT = [
      {
        devid: 1,
        packetid: 1,
        humid: 50.1,
        temp: 20.1,
      }, 
      {
        devid: 1,
        packetid: 2,
        humid: 50.2,
        temp: 20.2,
      }, 
      {
        devid: 1,
        packetid: 3,
        humid: 50.3,
        temp: 20.3,
      }, 
        {
        devid: 1,
        packetid: 4,
        humid: 50.4,
        temp: 20.4,
      },
      {
        devid: 1,
        packetid: 5,
        humid: 50.5,
        temp: 20.5,
      },
       {
        devid: 1,
        packetid: 6,
        humid: 50.6,
        temp: 20.6,
      },
      {
        devid: 1,
        packetid: 7,
        humid: 50.7,
        temp: 20.7,
      },
      {
        devid: 2,
        packetid: 2,
        humid: 50.2,
        temp: 20.2,
      },

      {
        devid: 5,
        packetid: 3,
        humid: 50.3,
        temp: 20.3,
      },

      {
        devid: 5,
        packetid: 4,
        humid: 50.4,
        temp: 20.4,
      },

      {
        devid: 5,
        packetid: 5,
        humid: 51.5,
        temp: 21.5,
      },

      {
        devid: 5,
        packetid: 6,
        humid: 59.6,
        temp: 29.6,
      },

      {
        devid: 5,
        packetid: 7,
        humid: 53.7,
        temp: 23.7,
      },
      {
        devid: 7,
        packetid: 1,
        humid: 71.1,
        temp: 31.1,
      },
      {
        devid: 7,
        packetid: 2,
        humid: 76.2,
        temp: 36.2,
      },

      {
        devid: 7,
        packetid: 3,
        humid: 73.3,
        temp: 33.3,
      },

      {
        devid: 7,
        packetid: 4,
        humid: 79.4,
        temp: 39.4,
      },
    ];
    async.each(BOOTSTRAP_DATA_COLLECT, function findOrCreateEachfakeData(fakeData, next){

      Data_collect.findOne({
        devid: fakeData.devid
      }).exec(function (err, existingData){
        if (err) return next(err);
        if (existingData) {
          return next();
        }
        });

      Data_collect.create({
            devid: fakeData.devid,
            packetid: fakeData.packetid,
            humid: fakeData.humid,
            temp: fakeData.temp,
           
          }).exec(function(err, createdData) {
            if (err) {
              return next(err);
            }
            return next();
          }); //</Data_collect.create()>
    }); 

    //fake Dev List
    var BOOTSTRAP_DEVICE_LIST = [
      {
        devid: 1,
        devname: 'Fast1',
        parameter: 'C7NDZ51',
        owner: 1,
        valid: true,
      },
      {
        devid: 2,
        devname: 'Fast2',
        parameter: 'C7NDZ52',
        owner: 1,
        valid: false,
      }, 
      {
        devid: 3,
        devname: 'Fast3',
        parameter: 'C7NDZ53',
        owner: 2,
        valid: false,
      }, 
      {
        devid: 4,
        devname: 'Fast4',
        parameter: 'C7NDZ54',
        owner: 2,
        valid: true,
      }, 
      {
        devid: 5,
        devname: 'Fast5',
        parameter: 'C7NDZ55',
        owner: 3,
        valid: true,
      },  
      {
        devid: 6,
        devname: 'Fast6',
        parameter: 'C7NDZ56',
        owner: 3,
        valid: false,
      },
      {
        devid: 7,
        devname: 'Fast7',
        parameter: 'C7NDZ57',
        owner: 3,
        valid: true,
      },
      {
        devid: 8,
        devname: 'Fast8',
        parameter: 'C7NDZ58',
        owner: 4,
        valid: false,
      },
    ];
    async.each(BOOTSTRAP_DEVICE_LIST, function findOrCreateEachfakeData(fakeData, next){
      Device.findOne({
        devid: fakeData.devid
      }).exec(function (err, existingData){
        if (err) return next(err);
        if (existingData) {
          return next();
        }
      });
      Device.create({
            devid: fakeData.devid,
            devname: fakeData.devname,
            parameter: fakeData.parameter,
            owner: fakeData.owner,
            valid: fakeData.valid,
          }).exec(function(err, createdData) {
            if (err) {
              return next(err);
            }
            return next();
          }); //</Data_collect.create()>
    }); 

     //fake Threshold List
    var BOOTSTRAP_THRESHOLD_LIST = [
      {
        devid: 1,
        upperHumid: 91,
        lowerHumid: 71,
        upperTemp: 41,
        lowerTemp: 21,
        owner: 2,
      },
      {
        devid: 2,
        upperHumid: 92,
        lowerHumid: 72,
        upperTemp: 42,
        lowerTemp: 22,
        owner: 2,
      },
      {
        devid: 3,
        upperHumid: 93,
        lowerHumid: 73,
        upperTemp: 43,
        lowerTemp: 23,
        owner: 2,
      },
      {
        devid: 4,
        upperHumid: 94,
        lowerHumid: 74,
        upperTemp: 44,
        lowerTemp: 24,
        owner: 2,
      },
      {
        devid: 5,
        upperHumid: 95,
        lowerHumid: 75,
        upperTemp: 45,
        lowerTemp: 25,
        owner: 3,
      },
      {
        devid: 6,
        upperHumid: 96,
        lowerHumid: 76,
        upperTemp: 46,
        lowerTemp: 26,
        owner: 3,
      },
      {
        devid: 7,
        upperHumid: 97,
        lowerHumid: 77,
        upperTemp: 47,
        lowerTemp: 27,
        owner: 3,
      },
      {
        devid: 8,
        upperHumid: 98,
        lowerHumid: 78,
        upperTemp: 48,
        lowerTemp: 28,
        owner: 2,
      },
    ];
    async.each(BOOTSTRAP_THRESHOLD_LIST, function findOrCreateEachfakeData(fakeData, next){
      Threshold.findOne({
        devid: fakeData.devid
      }).exec(function (err, existingData){
        if (err) return next(err);
        if (existingData) {
          return next();
        }
      });/*Threshold.findOne*/
      Threshold.create({
            devid: fakeData.devid,
            upperHumid: fakeData.upperHumid,
            lowerHumid: fakeData.lowerHumid,
            upperTemp: fakeData.upperTemp,
            lowerTemp: fakeData.lowerTemp,
            owner: fakeData.owner,
          }).exec(function(err, createdData) {
            if (err) {
              return next(err);
            }
            return next();
          }); //</Threshold.create()>
    }); 

    ///Finally
    console.log('------------------------------------------------------------------\nServer powered by: ' + os.platform() + ' ' +os.release() + ' ' + os.arch() + '\n');
    console.log('------------------------------------------------------------------\nServer hardware info: \n\n'  + JSON.stringify(os.cpus())+ '\n');
    console.log('------------------------------------------------------------------\nUser info: \n' + JSON.stringify(os.userInfo('username')));
   
   //GET Public IP address
   request('https://api.ipify.org', function (error, response, body) {
      if(error) {
        console.log('error:', error); // Print the error if one occurred
        console.log('statusCode:', response && response.statusCode); // Print the response status code if a response was received
      }

      console.log('Server IP:', body); // Print the HTML for the Google homepage.
      console.log('------------------------------------------------------------------\nGet access to homepage: http://' + body + ':'+ 8000)
      console.log('\n------------------------------------------------------------------\n')
    });
    return cb();
   });

};
