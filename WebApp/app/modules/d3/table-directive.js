(function() {
    'use strict';

    angular
        .module('d3')
        .directive('TableDirective', TableDirective); //will be named <bar-chart-directive>

    TableDirective.$inject = ['$state'];

    function TableDirective($state) {
        var directive = {
        	restricted: 'E', //use directive as an element
        	replace: false,
            scope: true,
        	bindToController:{ //create isolated scope
				data: "=", //this is same as @data - = defines two way binding
        	},
            controller:
            ['$scope', '$state',
                function TableDirective($scope, $state){
                    var y = EarthquakeFactory.getNearbyCities();
                    y.then(function(result) {
                        var x = result;
                    }
                }
            ],
        	link: link
        };
        return directive;
	}

})();
