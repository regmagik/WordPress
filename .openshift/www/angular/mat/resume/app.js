
(function(){
  var app = angular.module('myResume', []);
  app.controller('PersonController', function(){
    this.name = 'Matthew Guzner';
    this.email = 'mat@RegmagiK.com';
    this.contact = 'http://www.regmagik.com/contact/';
    this.openContact = function(){
      window.location = this.contact;
    };
  });
  app.controller('ExperienceController', function(){
    this.experience = [ 
      {id:21, from:'1/08/2016', to:'present', position:'student', company:'Brookwood Elementary'},
      {id:32, from:'08/14/2010', to:'12/16/2015', position:'Student', company:'Yargo Elementary'}
    ];
  });
})();