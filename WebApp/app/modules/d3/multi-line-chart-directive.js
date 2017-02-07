(function() {
    'use strict';

    angular
        .module('d3')
        .directive('multiLineChartDirective', multiLineChartDirective); //will be named <multi-line-chart-directive>

    multiLineChartDirective.inject = ['$state'];
    function multiLineChartDirective($state) {
        // Usage:
        //
        // Creates:
        //
        var directive = {
            restricted: 'E',
            replace: false,
            scope:{
                data: "=" //two way binding
            },
            link: link
        };
        return directive;
        
        function link(scope, element, attrs) {
            var chart = d3.select(element[0]);

            var margin = {top:20, right:80, bottom:30, left:50},
                width = 960 - margin.left - margin.right,
                height = 500 - margin.top - margin.bottom;

            var parseTime = d3.timeParse("%d-%b-%y");
            var formatTime = d3.timeFormat("%d-%b-%y");

            var x = d3.scaleTime().range([0, width]),
                y = d3.scaleLinear().range([height, 0]);

            var temperature = d3.line()
                .x(function(d){
                    //console.log(d);
                    return x(d.measuredAt);
                })
                .y(function(d){
                    //console.log("Temp: " + d.measuredTemperature);
                    return y(+d.measuredTemperature);
                });
            
            var humidity = d3.line()
                .x(function(d){
                    // console.log(d);
                    return x(d.measuredAt);
                })
                .y(function(d){
                    //console.log("Humid: " + d.humidity);
                    return y(+d.humidity);
                });
            
            var svg = chart.append("svg")
                .attr("width", width + margin.left + margin.right)
                .attr("height", height + margin.top + margin.bottom)
                .append("g")
                .attr("transform", "translate("+margin.left+","+margin.top+")");

            //console.log(scope.data.data);

            function assingValue(temp){
                if(temp == null){
                    return 0;
                }else{
                    return +temp;
                }
            }

            var data = scope.data;
            data.forEach(function(d){
                d.measuredAt = formatTime(new Date(d.measuredAt));
                d.measuredTemperature = assingValue(d.measuredTemperature);
                d.humidity = assingValue(d.humidity);
            });

            x.domain(d3.extent(data, function(d){
                return d.measuredAt;
            }));
            y.domain([0, d3.max(data, function(d){
                return Math.max(d.measuredTemperature, d.humidity);
            })]);

            svg.append("path")
                .data([data])
                .attr("class", "line")
                .attr("d", temperature);

            svg.append("path")
                .data([data])
                .attr("class", "line")
                .style("stroke", "red")
                .attr("d", humidity);
            
            svg.append("g")
                .attr("transform", "translate(0,"+height+")")
                .call(d3.axisBottom(x));

            svg.append("g")
                .call(d3.axisLeft(y));
        }
    }
})();