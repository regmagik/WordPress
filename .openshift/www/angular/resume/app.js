(function(){
  var app = angular.module('myResume', []);
  app.controller('PersonController', function(){
    this.name = 'Boris Guzner';
    this.email = 'boris@RegmagiK.com';
    this.contact = 'http://www.regmagik.com/contact/';
    this.openContact = function(){
      window.location = this.contact;
    };
  });
   var cir = 'Cambridge Investment Research';
  app.controller('ExperienceController', function(){
    this.experience = [ 
{id:11, from:'May 2015', to:'August 2015', position:'Tech Lead', company:'EY'},
{id:21, from:'11/11/2013', to:'March 2015', position:'Solutions Architect', company:cir},
{id:32, from:'06/06/2010', to:'11/11/2013', position:'Architect', company:cir	}
];
});
})();