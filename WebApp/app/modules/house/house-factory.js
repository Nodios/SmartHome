(function() {
'use strict';

    angular
        .module('house')
        .factory('HouseFactory', HouseFactory);

    HouseFactory.inject = ['$http'];
    function HouseFactory($http) {
        var self = this;

        var service = {
            getTemperatureAndHumidity: getTemperatureAndHumidity
        };
        
        return service;

        ////////////////
        function getTemperatureAndHumidity(){
            return $http.get("http://smart-home-tkr.azurewebsites.net/api/Temperature")
                .success(function(response){
                    console.log(response);
                    return response;
                })
                .error(function(err){
                    console.log(err);
                })
        }
    }
})();