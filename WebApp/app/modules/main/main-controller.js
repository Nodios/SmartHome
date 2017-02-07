(function() {
    'use strict';

    angular
        .module('app')
        .controller('MainController', MainController);

    MainController.$inject = ['$scope', '$state'];


    function MainController($scope, $state) {
        var self = this;
        
        $scope.title = "SmartHome";

        activate();

        function activate() {
        }
    }
})();