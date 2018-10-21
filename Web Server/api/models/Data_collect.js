/**
 * Data_collect.js
 *
 * @description :: TODO: You might write a short summary of how this model works and what it represents here.
 * @docs        :: http://sailsjs.org/documentation/concepts/models-and-orm/models
 */

module.exports = {

  attributes: {
    id: {
      type: 'integer',
      autoIncrement: true,
      primaryKey: true,
      unique: true
    },

  	devid: {
  		type: 'integer',
      unique: false
  	},

  	packetid: {
      type: 'integer',
      //required: true
  	},

  	humid: {
      type: 'float',
      defaultsTo: 0.0
    },

  	temp: {
      type: 'float',
      defaultsTo: 0.0
    },

  }
};

