(function() {
    'use strict';

    var app = angular.module('app', [
    	'ngResource', 
    	'ngRoute',
    	'ngSanitize',
    	'ui.router',
    	'd3',
    	'house'
    ]);

    app.config(config);

    config.$inject = ['$stateProvider', '$httpProvider', '$locationProvider', '$urlRouterProvider', '$urlMatcherFactoryProvider'];

	function config($stateProvider, $httpProvider, $locationProvider, $urlRouterProvider, $urlMatcherFactoryProvider) {
		$httpProvider.defaults.useXDomain = true;

		delete $httpProvider.defaults.headers.common['X-Requested-With'];

		$urlRouterProvider.otherwise('/');
		$urlRouterProvider.rule(function ($injector, $location) {
			var path = $location.path(),
				normalized = path.toLowerCase();
			if (path != normalized) {
				$location.replace().path(normalized);
			}
		});
		$urlMatcherFactoryProvider.caseInsensitive(true);
		$urlMatcherFactoryProvider.strictMode(false);
		$locationProvider.html5Mode({enabled: true, requireBase: false});

		$stateProvider
			.state('root', {
				url: '',
				views: {
					'root': {
						templateUrl: 'modules/main/main.html',
						controller: 'MainController'
					}
				}
			})
			.state('root.house', {
				url: '/house',
				views: {
					'main-content@root':{
						templateUrl: 'modules/house/house.html',
						controller: 'HouseController'
					}
				}
			});
			// .state('root.earthquakes.earthquake', {
			// 	url: '/earthquake',
			// 	views: {
			// 		'main-content@root':{
			// 			templateUrl: 'modules/earthquakes/earthquake.html',
			// 			controller: 'EarthquakeController'
			// 		}
			// 	},
			// 	params: { earthquakeUrl: undefined }
			// });
	}

	app.run(function ($state) {
		$state.go('root');
	});
})();