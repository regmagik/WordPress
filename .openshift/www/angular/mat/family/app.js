
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
  app.controller('FamilyController', function(){
    this.relatives = [ 
      {id:32,  relation:'Mom', name:'Kateryna', pictures:["p1", "p2"]},
      {id:22,  relation:'Dad', name:'Boris', pictures:["p3", "p4"]},
      {id:12,  relation:'Sister', name: 'Sonia', pictures:["p5", "p6"]}
    ];
  });
})();