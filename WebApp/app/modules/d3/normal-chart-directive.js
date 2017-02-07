(function() {
    'use strict';

    angular
        .module('d3')
        .directive('normalChartDirective', normalChartDirective); //will be named <bar-chart-directive>

    normalChartDirective.$inject = ['$state'];

    function normalChartDirective($state) {
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

            var margin = {top: 20, right: 20, bottom: 70, left: 40},
                width = 1500 - margin.left - margin.right,
                height = 500 - margin.top - margin.bottom;

            var placesArray = [];
            for(var i = 0; i < scope.data.length; i++){
                placesArray[i] = scope.data[i].properties.place;
            }

            var barPadding=4;
            var barWidth=width/scope.data.length-barPadding;

            var x = d3.scale.ordinal().domain(d3.range(scope.data.length)).rangeRoundBands([0,width]);
            var y = d3.scale.linear().domain([0,d3.max(scope.data,function(d){return d.properties.mag;})]).range([height, 0]);
            var xAxis = d3.svg.axis().scale(x).orient("bottom").tickFormat(function(d){
                if(scope.data.length < 20){return placesArray[d];}
                else{return "";}
            });
            var yAxis = d3.svg.axis().scale(y).orient("left").ticks(4);

            var tip = d3.tip()
                .attr("id", "tip")
                .attr('class', 'd3-tip')
                .offset([-10, 0])
                .html(function(d) {
                    return "<span>" + d.properties.place + "<br>with magnitude of <strong  style='color:red'>"+ d.properties.mag +"</strong></span>";
                })
            

            var svg = chart
                .append("svg")
                .attr("width", "100%")
                .attr("height", height + margin.top + margin.bottom+200)
                .append("g")
                .attr("transform","translate(" + margin.left + "," + margin.top + ")");

            svg.call(tip);

            svg.append("g")
                .attr("class","x axis")
                .attr("transform","translate(0,"+height+")")
                .call(xAxis)
                .selectAll("text")
                .attr("transform", function(d) {return "rotate(-25)"})
                .style("text-anchor","end");

            svg.append("g")
                .attr("class","y axis")
                .call(yAxis)
                .append("text")
                .attr("transform","rotate(-90)")
                .attr("y",6)
                .attr("dy",".71em")
                .style("text-anchor","end")
                .text("magnitude");

            var color = d3.scale.category10().domain(d3.range(scope.data.length));
            var normalChart = svg.selectAll("rect")
                .data(scope.data)
                .enter()
                .append("rect")
                .attr("x", function(d, i) { 
                    return x(i); 
                })
                .attr("y",function(d) { 
                    return y(d.properties.mag); 
                })
                .attr("width", barWidth)
                .attr("height", function(d) {
                    if((height - y(d.properties.mag)) < 0){
                        return 0;
                    }
                    else{
                        return height - y(d.properties.mag); 
                    }
                })
                .attr("fill",function(d,i){
                    return color(i)
                })
                .on('mouseover', tip.show)
                .on('mouseout', tip.hide)
                .on('click', getData);

            function getData(event){
                angular.element(document.querySelector('#tip')).remove();
                $state.go('root.earthquakes.earthquake', {earthquakeUrl: event.properties.detail});
            }
        }



	}

})();
