(function() {
'use strict';

    angular
        .module('house')
        .controller('HouseController', HouseController);

    HouseController.inject = ['$scope', '$state', 'HouseFactory'];

    function HouseController($scope, $state, HouseFactory) {
        var self = this;

        $scope.outputData = null;
        $scope.dataLoaded = false;

        var data = HouseFactory.getTemperatureAndHumidity();
        data.then(function(result){
            $scope.outputData = result.data;
            $scope.dataLoaded = true;
        });
    }
})();