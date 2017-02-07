(function() {
    'use strict';

    angular
        .module('d3')
        .directive('barChartDirective', BarChartDirective); //will be named <bar-chart-directive>

    BarChartDirective.$inject = [];

    function BarChartDirective() {
        var directive = {
        	restricted: 'E', //use directive as an element
        	replace: false,
        	scope:{ //create isolated scope
				data: "=", //this is same as @data - = defines two way binding
        	},
        	link: link
        };
        return directive;

        function link(scope, element, attrs) {
        	var chart = d3.select(element[0]);

        	chart
        		.append("div")
        		//.attr("class", "chart")
        		.selectAll("div")
        		.data(scope.data)
        		.enter()
        		.append("div")
        		.style({
        			"background": "steelblue",
        			"color": "white",
        			"width": function(d) 
                        {
                            if(d.properties.mag >= 0){
                                return d.properties.mag +"%";
                            }else{
                                return "0%";
                            }
                        },
        			"padding": "3px",
        			"margin": "3px",
        			"box-shadow": "2px 2px 2px #666"

        		})
        		.text(function(d) {return d.properties.mag;});

        		
        }

	}

})();
