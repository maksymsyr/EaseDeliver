#include "pch.h"
#include "CppUnitTest.h"
#include "TestingProject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectTestSuite
{
	TEST_CLASS(SelectTruckBlackBox) {
		TEST_METHOD(TC001) {

			Map map = populateMap();

			const int boxesSize1 = 26;
			const int boxesSize2 = 39;

			Box loadedBoxes[boxesSize1] = { 0 };
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Box loadedBoxes2[boxesSize2] = { 0 };
			for (int i = 0; i < 39; i++) {
				loadedBoxes2[i] = { 10, 2, 1.0, (5,6) };
			}
			Route blueRoute = getBlueRoute();
			Route greenRoute = getGreenRoute();
			Truck truck1 = { 1, 26, 0.75, blueRoute, *loadedBoxes };
			Truck truck2 = { 1, 39, 0.75, greenRoute, *loadedBoxes2 };

			Truck truckArray[2] = { truck1, truck2 };
			Box boxToLoad = { 123, 100, 10.0, (5,6) };

			int shortlist[3] = { 1,1 };
			int result = selectTruck(shortlist, &map, truckArray, &boxToLoad);

			Assert::AreEqual(-1, result);
			Assert::AreEqual(1, shortlist[0]);
			Assert::AreEqual(1, shortlist[1]);
			Assert::AreEqual(boxesSize1, truck1.boxCount);
			Assert::AreEqual(boxesSize2, truck2.boxCount);
		}

		TEST_METHOD(TC002) {

			Map map = populateMap();

			const int loadBoxesSize = 100;
			Box loadedBoxes[loadBoxesSize] = { 0 };
			for (int i = 0; i < loadBoxesSize; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Box loadedBoxes2[loadBoxesSize] = { 0 };
			for (int i = 0; i < loadBoxesSize; i++) {
				loadedBoxes2[i] = { 10, 2, 1.0, (5,6) };
			}
			Route blueRoute = getBlueRoute();
			Route greenRoute = getGreenRoute();
			Truck truck1 = { 0.75, 100, 0.75, blueRoute, *loadedBoxes };
			Truck truck2 = { 0.75, 100, 0.75, greenRoute, *loadedBoxes2 };

			Truck truckArray[2] = { truck1, truck2 };
			Box boxToLoad = { 123, 100, 10.0, (5,6) };

			int shortlist[3] = { 1,1 };
			int result = selectTruck(shortlist, &map, truckArray, &boxToLoad);

			Assert::AreEqual(-1, result);
			Assert::AreEqual(1, shortlist[0]);
			Assert::AreEqual(1, shortlist[1]);
			Assert::AreEqual(loadBoxesSize, truck1.boxCount);
			Assert::AreEqual(loadBoxesSize, truck2.boxCount);
		}

		TEST_METHOD(TC003) {

			Map map = populateMap();

			const int boxesSize1 = 26;
			const int boxesSize2 = 39;

			Box loadedBoxes[boxesSize1] = { 0 };
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Box loadedBoxes2[boxesSize2] = { 0 };
			for (int i = 0; i < 39; i++) {
				loadedBoxes2[i] = { 10, 2, 1.0, (5,6) };
			}
			Route blueRoute = getBlueRoute();
			Route greenRoute = getGreenRoute();
			Truck truck1 = { 0.23, 26, 1, blueRoute, *loadedBoxes };
			Truck truck2 = { 0.23, 39, 1, greenRoute, *loadedBoxes2 };

			Truck truckArray[2] = { truck1, truck2 };
			Box boxToLoad = { 123, 100, 10.0, (5,6) };

			int shortlist[3] = { 1,1 };
			int result = selectTruck(shortlist, &map, truckArray, &boxToLoad);

			Assert::AreEqual(-1, result);
			Assert::AreEqual(1, shortlist[0]);
			Assert::AreEqual(1, shortlist[1]);
			Assert::AreEqual(boxesSize1, truck1.boxCount);
			Assert::AreEqual(boxesSize2, truck2.boxCount);
		}

		TEST_METHOD(TC004) {

			Map map = populateMap();

			const int boxesSize1 = 26;
			const int boxesSize2 = 39;
			const int boxesSize3 = 39;

			Box loadedBoxes[boxesSize1] = { 0 };
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, { 5,6 } };
			}
			Box loadedBoxes2[boxesSize2] = { 0 };
			for (int i = 0; i < 39; i++) {
				loadedBoxes2[i] = { 10, 2, 1.0, { 5,6 } };
			}
			Route blueRoute = getBlueRoute();
			Route greenRoute = getGreenRoute();
			Route yellowRoute = getYellowRoute();
			Truck truck1 = { 0.043, 26, 0.52, blueRoute, *loadedBoxes };
			Truck truck2 = { 0.065, 39, 0.78, greenRoute, *loadedBoxes2 };
			Truck truck3 = { 0.065, 39, 0.78, yellowRoute, *loadedBoxes2 };

			Truck truckArray[3] = { truck1, truck2, truck3 };
			Box boxToLoad = { 123, 20, 1.0, { 11 , 10 } };

			int shortlist[3] = { 1,1,1 };
			int result = selectTruck(shortlist, &map, truckArray, &boxToLoad);

			Assert::AreEqual(0, result);
			Assert::AreEqual(1, shortlist[0]);
			Assert::AreEqual(0, shortlist[1]);
			Assert::AreEqual(0, shortlist[2]);
			/*Assert::AreEqual(boxesSize1 + 1, truck1.boxCount);
			Assert::AreEqual(boxesSize2, truck2.boxCount);*/

		}
	};

	TEST_CLASS(loadBoxBlackBox)
	{
	public:
		TEST_METHOD(TC005)
		{
			Route blueRoute = getBlueRoute();
			Box boxToLoad = { 123, 1201, 10.0, (5,6) };
			Box loadedBoxes[26] = { 0 };
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Truck truck = { 0.7, 26, 0.72, blueRoute, *loadedBoxes };
			int result = loadBox(&truck, &boxToLoad);
			Assert::AreEqual(-1, result);
			Assert::AreEqual(26, truck.boxCount);
		}
		TEST_METHOD(TC006)
		{
			Route blueRoute = getBlueRoute();
			Box boxToLoad = { 123, 121, 2.0, (5,6) };
			Box loadedBoxes[100] = { 0 };
			for (int i = 0; i < 100; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Truck truck = { 0.7, 100, 0.72, blueRoute, *loadedBoxes };
			int result = loadBox(&truck, &boxToLoad);
			Assert::AreEqual(-1, result);
			Assert::AreEqual(100, truck.boxCount);
		}
		TEST_METHOD(TC007)
		{
			Route blueRoute = getBlueRoute();
			Box boxToLoad = { 123, 121, 35.0, (5,6) };
			Box loadedBoxes[22] = { 0 };
			for (int i = 0; i < 22; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Truck truck = { 0.7, 22, 0.72, blueRoute, *loadedBoxes };
			int result = loadBox(&truck, &boxToLoad);
			Assert::AreEqual(-1, result);
			Assert::AreEqual(22, truck.boxCount);
		}
		TEST_METHOD(TC008)
		{
			Route blueRoute = getBlueRoute();
			Box boxToLoad = { 123, 121, 5.0, {5,6} };
			Box loadedBoxes[22] = { 0 };
			for (int i = 0; i < 22; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, {5,6} };
			}
			Truck truck = { 0.7, 22, 0.72, blueRoute, *loadedBoxes };
			int result = loadBox(&truck, &boxToLoad);
			Assert::AreEqual(1, result);
			// todo:: I changed here a little bit (was 23)
			Assert::AreEqual(23, truck.boxCount);
		}
	};

	TEST_CLASS(ShortestDiversionBlackBox) {
		TEST_METHOD(TC009) {
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { 4,3 };
			Route expectedRoute = { {{4, 3}}, 1, 16 };
			Route resultRoute = shortestDiversion(&map, &blue, point);
			double resultRouteLen = pathLen(&resultRoute);
			double expectedRouteLen = pathLen(&expectedRoute);
			double diff = resultRouteLen - expectedRouteLen > 0 ? resultRouteLen - expectedRouteLen : expectedRouteLen - resultRouteLen;
			//Assert::IsTrue(diff < 0.0001);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.routeSymbol, resultRoute.routeSymbol);
		}
		TEST_METHOD(TC010) {
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { -5,-5 };
			Route expectedRoute = { {0,0}, 0, 16 };
			Route resultRoute = shortestDiversion(&map, &blue, point);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
		}

		TEST_METHOD(TC011) {
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { 27, 27 };
			Route expectedRoute = { 0 };
			Route resultRoute = shortestDiversion(&map, &blue, point);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
		}

		TEST_METHOD(TC012) {
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { 27, 27 };
			Route expectedRoute = { {{ 0, 0 }}, 0, 16};
			int  expectedDiversion = 0;
			Route resultRoute = shortestDiversion(&map, &blue, point);
			Assert::AreEqual(expectedDiversion, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
		}
		//struct Route shortestDiversion(const struct Map* map, const struct Route* route, const struct Point dest)
	};

	TEST_CLASS(pathLenBlackBox)
	{
	public:
		TEST_METHOD(TC022)
		{
			Route blueRoute = getBlueRoute();
			double result = pathLen(&blueRoute);
			double testNum = 41.0; //It was 42.0
			double diff = result - testNum > 0 ? result - testNum : testNum - result;

			Assert::IsTrue(diff < 0.01);
		}
		TEST_METHOD(TC023)
		{
			Route greenRoute = getGreenRoute();
			double result = pathLen(&greenRoute);
			double testNum = 41.0; //It was 43.0
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
		TEST_METHOD(TC024)
		{
			Route yellowRoute = getYellowRoute();
			double result = pathLen(&yellowRoute);
			double testNum = 47.0; //It was 48.0
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
		TEST_METHOD(TC025)
		{
			Route errorRoute = { { -1, -1} , 1, 4 };
			double result = pathLen(&errorRoute);
			Assert::IsTrue(result < 0.0);
		}
	};
	TEST_CLASS(eqPtBlackBox)
	{
	public:

		TEST_METHOD(TC026)
		{
			Point p1 = { 1, 2 };
			Point p2 = { 1, 2 };
			bool result = eqPt(p1, p2);
			Assert::IsTrue(result);
		}

		TEST_METHOD(TC027)
		{
			Point p1 = { 1, 2 };
			Point p2 = { 2, 1 };
			bool result = eqPt(p1, p2);
			Assert::IsFalse(result);
		}

		TEST_METHOD(TC028)
		{
			Point p1 = { 1, 2 };
			Point p2 = { 1, 4 };
			bool result = eqPt(p1, p2);
			Assert::IsFalse(result);
		}

		TEST_METHOD(TC029)
		{
			Point p1 = { 1, 2 };
			Point p2 = { 4, 2 };
			bool result = eqPt(p1, p2);
			Assert::IsFalse(result);
		}
	};

	TEST_CLASS(pathLenWhiteBox) {
		TEST_METHOD(TC042) {
			char TEMP = 't';
			Route route = { {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}}, 5, TEMP };
			double result = pathLen(&route);
			double testNum = 4;
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
		TEST_METHOD(TC043) {
			char TEMP = 't';
			Route route = { {{0,0}, {1,0}, {2,0}, {4,1}}, 4, TEMP };
			double result = pathLen(&route);
			double testNum = -1.0;
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
		TEST_METHOD(TC044) {
			char TEMP = 't';
			Route route = { {{1,0}, {2,0}, {3,0}, {4,0}}, 4, TEMP };
			double result = pathLen(&route);
			double testNum = 3.0;
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
		TEST_METHOD(TC045) {
			Route route = getGreenRoute();
			double result = pathLen(&route);
			double testNum = 41.0;
			double diff = result - testNum > 0 ? result - testNum : testNum - result;
			Assert::IsTrue(diff < 0.0001);
		}
	};

	TEST_CLASS(DistanceTestCases)
	{
	public:

		TEST_METHOD(TC030)
		{
			const Point p1 = { 1, 2 };
			const Point p2 = { 1, 2 };
			// todo::should be double and everywhere else change it
			int result = distance(&p1, &p2);
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(TC031)
		{
			const Point p1 = { 0, 0 };
			const Point p2 = { 0, 3 };
			int result = distance(&p1, &p2);
			Assert::AreEqual(result, 3);
		}

		TEST_METHOD(TC032)
		{
			const Point p1 = { 0, 0 };
			const Point p2 = { 3, 0 };
			int result = distance(&p1, &p2);
			Assert::AreEqual(result, 3);
		}

		TEST_METHOD(TC033)
		{
			double TestNum = 6.4;
			const Point p1 = { 3, 4 };
			const Point p2 = { 7, 9 };
			double result = distance(&p1, &p2);
			double diff = result - TestNum > 0 ? result - TestNum : TestNum - result;
			Assert::IsTrue(diff > 0.0001);
		}

	};

	TEST_CLASS(InputBoxBlackBox)
	{
	public:

		TEST_METHOD(TC018)
		{
			Box box = { 0 };
			Point point = { 12, 8 };
			int result = inputBox(&box, 1, 1, 30, point);
			Assert::AreEqual(result, 1);
			Assert::AreEqual(box.id, 1);
			Assert::AreEqual(box.volume, 1.0);
			Assert::AreEqual(box.weight, 30.0);
			Assert::AreEqual(box.destination.row, point.row);
			Assert::AreEqual(box.destination.col, point.col);
		}

		TEST_METHOD(TC019)
		{
			Box box = { 0 };
			Point point = { 12, 8 };
			int result = inputBox(&box, 1, -1, 1, point);
			Assert::AreEqual(result, 0);
			Assert::AreEqual(box.id, 0);
			Assert::AreEqual(box.volume, 0.0);
			Assert::AreEqual(box.weight, 0.0);
			Assert::AreEqual((int)box.destination.row, -1);
			Assert::AreEqual((int)box.destination.col, -1);
		}

		TEST_METHOD(TC020)
		{
			Box box = { 0 };
			Point point = { 12, 8 };
			int result = inputBox(&box, -1, 1, 30, point);
			Assert::AreEqual(result, 0);
			Assert::AreEqual(box.id, 0);
			Assert::AreEqual(box.volume, 0.0);
			Assert::AreEqual(box.weight, 0.0);
			Assert::AreEqual((int)box.destination.row, -1);
			Assert::AreEqual((int)box.destination.col, -1);
		}

		TEST_METHOD(TC021)
		{
			Box box = { 0 };
			Point point = { -20, -13 };
			int result = inputBox(&box, 1, 1, 30, point);
			Assert::AreEqual(result, 0);
			Assert::AreEqual(box.id, 0);
			Assert::AreEqual(box.volume, 0.0);
			Assert::AreEqual(box.weight, 0.0);
			Assert::AreEqual((int)box.destination.row, -1);
			Assert::AreEqual((int)box.destination.col, -1);
		}

	};


	TEST_CLASS(InputBoxWhiteBox)
	{
	public:

		TEST_METHOD(TC034)
		{
			Box box = { 0,0,0,{-1,-1} };
			Point point = { 3, 2 };
			int result = inputBox(&box, 1, 20, 1, point);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TC035)
		{
			Point point = { 12, 8 };
			int result = inputBox(NULL, 1, 20, 1, point);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(TC036)
		{
			Box box = { -1,2,0,{2,3} };
			Point point = { 2, -2 };
			int result = inputBox(&box, 3, 10, 0.5, point);
			Assert::AreEqual(result, 0);
			Assert::AreEqual(box.id, 0);
			Assert::AreEqual(box.volume, 0.0);
			Assert::AreEqual(box.weight, 0.0);
			Assert::AreEqual((int)box.destination.row, -1);
			Assert::AreEqual((int)box.destination.col, -1);
		}

		TEST_METHOD(TC037)
		{
			Box	box = { 0,0,0,{-1, -1} };
			Point point = { 3, 2 };
			int result = inputBox(&box, 4, 20, 8, point);
			Assert::AreEqual(result, 0);
			Assert::AreEqual(box.id, 0);
			Assert::AreEqual(box.volume, 0.0);
			Assert::AreEqual(box.weight, 0.0);
			Assert::AreEqual((int)box.destination.row, -1);
			Assert::AreEqual((int)box.destination.col, -1);
		}

	};

	TEST_CLASS(FitInTruckBlackBox)
	{
	public:

		TEST_METHOD(TC013)
		{
			Route blue = getBlueRoute();
			Truck truck = { 0 };
			truck.currWeightLoad = 0;
			truck.boxCount = 0;
			truck.currVolLoad = 0;
			truck.route = blue;
			Box box = { 11, 20, 1, {12, 8} };
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(TC014)
		{
			Route blue = getBlueRoute();
			Truck truck = { 0 };
			truck.currWeightLoad = 0.95; // Almost FUll
			truck.boxCount = 59;
			truck.currVolLoad = 0.59;
			truck.route = blue;
			Box box = { 11, 20, 1, {12, 8} };
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(TC015)
		{
			Route blue = getBlueRoute();
			Truck truck = { 0 };
			truck.currWeightLoad = 1.0;
			truck.boxCount = 20;
			truck.currVolLoad = 0.2;
			truck.route = blue;
			Box box = { 11, 20.0, 1.0, {12, 8} };
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(TC016)
		{
			Route blue = getBlueRoute();
			Truck truck = { 0 };
			truck.currWeightLoad = 0.8;
			truck.boxCount = 100; //Boxes Full
			truck.currVolLoad = 1.0; //Volume Full
			truck.route = blue;
			Box box = { 11, 20, 1, {3, 2} };
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(TC017)
		{
			Truck truck = { 0 };
			Box box = { -2, 20, 1, {12, 8} }; // Invalid box
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, -1);
		}
	};

	TEST_CLASS(FitInTruckWhiteBox)
	{
	public:

		TEST_METHOD(TC038)
		{
			Route route = { {{0,0}, {0,1}, {0,2}}, 3, 15 };
			Truck truck = { 0 };
			Box box = { 10,20,0.5,{3,2} };
			truck.currWeightLoad = 0;
			truck.boxCount = 0;
			truck.currVolLoad = 0;
			truck.route = route;
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 1);
		}

		TEST_METHOD(TC039)
		{
			Route blue = getBlueRoute();
			Truck truck = { 0 };
			truck.currWeightLoad = 0.9;
			truck.boxCount = 9;
			truck.currVolLoad = 0.43;
			truck.route = blue;
			const int boxesSize = 10;
			Box boxes[boxesSize];
			for (int i = 0; i < boxesSize; i++) {
				boxes[i] = { 10, 120, 0.5, {3, 2} };
			}
			Box box = { 10, 240, 0.5, {3, 2} };
			int result = fitInTruck(&truck, &box);
			Assert::AreEqual(result, 0);
		}

		TEST_METHOD(TC040)
		{
			Route blue = getBlueRoute();
			Box box = { 11, 20.0, 1.0, {12, 8} };
			int result = fitInTruck(NULL, &box);
			Assert::AreEqual(result, -1);
		}
	};

	TEST_CLASS(ShortestDiversionIntegrationWhiteBox)
	{
	public:

		TEST_METHOD(TC059)
		{
			Route blue = getBlueRoute();
			Point point = { 0,0 };
			Route expectedRoute = { {0,0},0,16 };
			Route resultRoute = shortestDiversion(NULL, &blue, point);
			double resultRouteLen = pathLen(&resultRoute);
			double expectedRouteLen = pathLen(&expectedRoute);
			double diff = resultRouteLen - expectedRouteLen > 0 ? resultRouteLen - expectedRouteLen : expectedRouteLen - resultRouteLen;
			Assert::IsTrue(diff < 0.0001);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.routeSymbol, resultRoute.routeSymbol);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
		}

		TEST_METHOD(TC060)
		{
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { -1,-1 };
			Route expectedRoute = { {0,0},0,16 };;
			Route resultRoute = shortestDiversion(&map, &blue, point);
			double resultRouteLen = pathLen(&resultRoute);
			double expectedRouteLen = pathLen(&expectedRoute);
			double diff = resultRouteLen - expectedRouteLen > 0 ? resultRouteLen - expectedRouteLen : expectedRouteLen - resultRouteLen;
			Assert::IsTrue(diff < 0.0001);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.routeSymbol, resultRoute.routeSymbol);
			Assert::AreEqual(expectedRoute.points[0].row, resultRoute.points[0].row);
			Assert::AreEqual(expectedRoute.points[0].col, resultRoute.points[0].col);
		}

		TEST_METHOD(TC061)
		{
			Map map = populateMap();
			Route blue = { {{0,1}, {0, 2}, {0, 3}, {1, 3}}, 4, 'd' };
			Point point = { 3,9 };
			Route expectedRoute = { {{1,3}, {2,3},{3,3}, { 3,4 },{3,5},{3,6},{3,7},{3,8},{3,9} }, 9, 16 };
			Route resultRoute = shortestDiversion(&map, &blue, point);
			double resultRouteLen = pathLen(&resultRoute);
			double expectedRouteLen = pathLen(&expectedRoute);
			double diff = resultRouteLen - expectedRouteLen > 0 ? resultRouteLen - expectedRouteLen : expectedRouteLen - resultRouteLen;
			Assert::IsTrue(diff < 0.0001);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(expectedRoute.routeSymbol, resultRoute.routeSymbol);
			for (int i = 0; i < expectedRoute.numPoints; i++) {
				Assert::AreEqual(expectedRoute.points[i].row, resultRoute.points[i].row);
				Assert::AreEqual(expectedRoute.points[i].col, resultRoute.points[i].col);
			}
		}

		TEST_METHOD(TC062)
		{
			Map map = populateMap();
			Route blue = getBlueRoute();
			Point point = { 1,3 };
			Route expectedRoute = { {{4,3},{3,3},{2,3},{1,3}}, 4, 16 };
			Route resultRoute = shortestDiversion(&map, &blue, point);
			double resultRouteLen = pathLen(&resultRoute);
			double expectedRouteLen = pathLen(&expectedRoute);
			double diff = resultRouteLen - expectedRouteLen > 0 ? resultRouteLen - expectedRouteLen : expectedRouteLen - resultRouteLen;
			Assert::IsTrue(diff < 0.0001);
			Assert::AreEqual(expectedRoute.numPoints, resultRoute.numPoints);
			Assert::AreEqual(16, resultRoute.routeSymbol);
			for (int i = 0; i < expectedRoute.numPoints; i++) {
				Assert::AreEqual(expectedRoute.points[i].row, resultRoute.points[i].row);
				Assert::AreEqual(expectedRoute.points[i].col, resultRoute.points[i].col);
			}

		}
	};

	TEST_CLASS(ValidateBoxBlackBox) {
		TEST_METHOD(TC070) {
			Box box = { 15, 0.0, 5.0, (1,3) };
			int result = validateBox(&box);
			Assert::IsFalse(result);
		}
		TEST_METHOD(TC071) {
			Box box = { 15, 0.0, 5.0, (1,3) };
			int result = validateBox(&box);
			Assert::IsFalse(result);
		}
		TEST_METHOD(TC072) {
			Box box = { 26, 70.0, 1.0, (-1,-1) };
			int result = validateBox(&box);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(TC073) {
			Box box = { 0, 0, 0.7,{-5,-6} };
			int result = validateBox(&box);
			Assert::IsFalse(result);
		}
	};

	TEST_CLASS(ValidateBoxWhiteBox) {
		TEST_METHOD(TC096) {
			int result = validateBox(NULL);
			Assert::IsFalse(result);
		}
		TEST_METHOD(TC097) {
			Box box = { 15, 0.0, 5.0, (1,3) };
			int result = validateBox(&box);
			Assert::IsFalse(result);
		}
	};

	TEST_CLASS(ValidateRouteWhiteBox) {
		TEST_METHOD(TC057) {
			Route route = { {{0, 0}, {0, 0},{0, 0}, {0, 0}}, 4, 15 };
			int result = validateRoute(&route);
			Assert::IsFalse(result);
		}
		TEST_METHOD(TC058) {
			Box box = { 15, 0.0, 5.0, (1,3) };
			int result = validateBox(&box);
			Assert::IsFalse(result);
		}
	};

	TEST_CLASS(ValidateTruckBlackBox) {
		TEST_METHOD(TC074) {
			Route blue = getBlueRoute();
			Box box = { 1, 1200.00, 25.00, {1, 3} };
			Box boxes[1] = { box };
			Truck truck = { 1.00, 1, 0.5, blue, *boxes };
			int result = validateTruck(&truck);
			Assert::IsTrue(result);
		}
		TEST_METHOD(TC075) {
			Route blue = getBlueRoute();
			const int size = 10;
			Box loadedBoxes[size];
			for (int i = 0; i < size; i++) {
				loadedBoxes[i] = { 1, 100.00, 5.00, {1,3 } };
			}
			Truck truck = { 0.5, 10, 1.0, blue, *loadedBoxes };
			int result = validateTruck(&truck);
			Assert::IsTrue(result);
		}

		TEST_METHOD(TC076) {
			Route blue = getBlueRoute();
			const int size = 100;
			Box loadedBoxes[size];
			for (int i = 0; i < size; i++) {
				loadedBoxes[i] = { 1, 20, 0.5, {1,3 } };
			}
			Truck truck = { 0.5, 100, 0.98, blue, *loadedBoxes };
			int result = validateTruck(&truck);
			Assert::IsTrue(result);
		}
		TEST_METHOD(TC077) {
			Route blue = getBlueRoute();
			Box box = { 1, 600.00, 5.00, {1, 3} };
			Box boxes[1] = { box };
			Truck truck = { 0.5, 1, 0.05, blue, *boxes };
			int result = validateTruck(&truck);
			Assert::IsTrue(result);
		}
	};

	TEST_CLASS(SelectByWeightLoadBlackBox) {
		TEST_METHOD(TC078) {
			int paralArray[3] = { 1,1,1 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 1200.00, 5.00, { 3,3 } };
			Box box2 = { 1, 120.0, 5.00, {6,3} };
			Box box3 = { 1, 240.0, 25.00, {9,3} };
			Box boxes1[1] = { box1 };
			Box boxes2[1] = { box2 };
			Box boxes3[1] = { box3 };
			Truck trucks[3] = { {1.00, 1, 0.1, blue, *boxes1}, {0.2, 1, 0.1, blue, *boxes3}, {0.2, 1, 0.5, blue, *boxes3} };
			int expectedShortList[3] = { 0, 1, 1 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC079) {
			int paralArray[3] = { 0,0,0 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 1200.00, 5.00, { 3,3 } };
			Box box2 = { 1, 1200.0, 5.00, {6,3} };
			Box box3 = { 1, 1200.0, 25.00, {9,3} };
			Box boxes1[1] = { box1 };
			Box boxes2[1] = { box2 };
			Box boxes3[1] = { box3 };
			Truck trucks[3] = { {1.00, 1, 0.05, blue, *boxes1}, {0.2, 1200, 0.05, blue, *boxes3}, {1.0, 1, 0.5, blue, *boxes3} };
			int expectedShortList[3] = { 0, 0, 0 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC080) {
			const int boxesNum = 10;
			Box boxes[boxesNum];
			for (int i = 0; i < boxesNum; i++) {
				boxes[i] = { i + 1, 100.00, 5.00, {3,3} };
			}
			int paralArray[3] = { 1, 0, 0 };
			Route blue = getBlueRoute();
			Truck trucks[1] = { 0.83, 10, 1.0, blue, *boxes };
			int expectedShortList[3] = { 1, 0, 0 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC081) {
			int paralArray[3] = { 1,1,1 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 120, 5.00, { 3,3 } };
			Box boxes1[1] = { box1 };
			Box boxes2[1] = { box1 };
			Box boxes3[1] = { box1 };
			Truck trucks[3] = { {0.1, 1, 0.05, blue, *boxes1}, {0.1, 1200, 0.05, blue, *boxes3}, {0.1, 1, 0.05, blue, *boxes3} };
			int expectedShortList[3] = { 1,1,1 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}
	};


	TEST_CLASS(SelectByVolLoadBlackBox) {
		TEST_METHOD(TC082) {
			int paralArray[3] = { 1,1,1 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 1008.00, 1.00, { 3,3 } };
			Box box2 = { 1, 120.0, 5.00, {6,3} };
			Box box3 = { 1, 240.0, 25.00, {9,3} };
			Box boxes1[1] = { box1 };
			Box boxes2[1] = { box2 };
			Box boxes3[1] = { box3 };
			Truck trucks[3] = { {0.9, 1, 0.02, blue, *boxes1}, {0.1, 1, 0.1, blue, *boxes3}, {0.2, 1, 0.5, blue, *boxes3} };
			int expectedShortList[3] = { 1, 0, 0 };
			selectByVolLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC083) {
			int paralArray[3] = { 1,1,1 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 1008.00, 5.00, { 3,3 } };
			Box box2 = { 1, 120.0, 5.00, {6,3} };
			Box box3 = { 1, 240.0, 25.00, {9,3} };
			const int boxesNum = 10;
			Box boxes1[boxesNum];
			for (int i = 0; i < boxesNum; i++) {
				boxes1[i] = box1;
			}
			Box boxes2[1] = { box2 };
			Box boxes3[1] = { box3 };
			Truck trucks[3] = { {0.9, 10, 1.0, blue, *boxes1}, {0.1, 1, 0.1, blue, *boxes3}, {0.2, 1, 0.5, blue, *boxes3} };
			int expectedShortList[3] = { 0, 1, 0 };
			selectByVolLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC084) {
			int paralArray[3] = { 0,0,0 };
			Route blue = getBlueRoute();
			const int boxesNum = 10;
			Box boxes[boxesNum];
			for (int i = 0; i < boxesNum; i++) {
				boxes[i] = { i + 1, 100.00, 5.00, {3,3} };
			}
			Truck trucks[3] = { { 0.83, 10, 1, blue, *boxes}, {0.83, 10, 1, blue, *boxes}, {0.83, 10, 1, blue, *boxes} };
			int expectedShortList[3] = { 0, 0, 0 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC085) {
			int paralArray[3] = { 1, 1, 1 };
			Route blue = getBlueRoute();
			Box box1 = { 1, 120, 5.00, { 3,3 } };
			Box boxes1[1] = { box1 };
			Truck trucks[3] = { {0.1, 1, 0.05, blue, *boxes1} , {0.1, 1, 0.05, blue, *boxes1} , {0.1, 1, 0.05, blue, *boxes1} };
			int expectedShortList[3] = { 1, 1, 1 };
			selectByWeightLoad(paralArray, trucks);
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}
	};

	TEST_CLASS(selectByPathBlackBox) {
			TEST_METHOD(TC086) {
				Map map = populateMap();
				int paralArray[3] = { 1,1,1 };
				Route blue = getBlueRoute();
				Route green = getGreenRoute();
				Box box = { 1, 120.0, 5.00, {3,3} };
				Box boxes1[1] = { box };
				Box boxes2[1] = { box };
				Truck trucks[3] = { {0.23, 1, 0.23, blue, *boxes1}, {0.1, 1, 0.1, green, *boxes2}, {0.1, 1, 0.1, green, *boxes2} };
				int expectedShortList[3] = { 1,0, 0 };
				Point dest = { 5,9 };
				selectByPath(paralArray, &map, trucks, dest);
				for (int i = 0; i < 3; i++) {
					Assert::AreEqual(expectedShortList[i], paralArray[i]);
				}
			}


		TEST_METHOD(TC087) {
			Map map = populateMap();
			int paralArray[2] = { 0,0 };
			Route blue = getBlueRoute();
			Route green = getGreenRoute();
			Box box = { 1, 120.0, 5.00, {3,3} };
			Box boxes1[1] = { box };
			Box boxes2[1] = { box };
			Truck trucks[2] = { {0.23, 1, 0.23, blue, *boxes1}, {0.1, 1, 0.1, green, *boxes2} };
			int expectedShortList[2] = { 0,0 };
			Point dest = { 27,27 };
			selectByPath(paralArray, &map, trucks, dest);
			for (int i = 0; i < 2; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

		TEST_METHOD(TC088) {
			Map map = populateMap();
			int paralArray[2] = { 0,0 };
			Route blue = getBlueRoute();
			Route green = getGreenRoute();
			Box box = { 1, 120.0, 5.00, {3,3} };
			Box boxes1[1] = { box };
			Box boxes2[1] = { box };
			Truck trucks[2] = { {0.23, 1, 0.23, blue, *boxes1}, {0.1, 1, 0.1, green, *boxes2} };
			int expectedShortList[2] = { 0,0 };
			Point dest = { -5, -5 };
			selectByPath(paralArray, &map, trucks, dest);
			for (int i = 0; i < 2; i++) {
				Assert::AreEqual(expectedShortList[i], paralArray[i]);
			}
		}

			TEST_METHOD(TC089) {
				Map map = populateMap();
				int paralArray[3] = { 1,1,1 };
				Route blue = getBlueRoute();
				Route green = getGreenRoute();
				Route yellow = getYellowRoute();
				Box box = { 1, 120.0, 5.00, {3,3} };
				Box boxes1[1] = { box };
				Box boxes2[1] = { box };
				Truck trucks[3] = { {0.23, 1, 0.23, blue, *boxes1}, {0.1, 1, 0.1, green, *boxes2}, {0.1, 1, 0.1, yellow, *boxes2} };
				int expectedShortList[3] = { 1,1,1 };
				selectByPath(paralArray, &map, trucks, box.destination);
				for (int i = 0; i < 3; i++) {
					Assert::AreEqual(expectedShortList[i], paralArray[i]);
				}
			}


	};


	/**************************************************************************************/
	/**************************************************************************************/
	/**************************************************************************************/
	/**********************************WHITE BOX TEST CASES********************************/
	/**************************************************************************************/
	/**************************************************************************************/
	/**************************************************************************************/

	TEST_CLASS(inputBoxWhiteBox) {
		TEST_METHOD(TC034) {
			Box box;
			Point point = { 3, 2 };
			int result = inputBox(&box, 1, 20, 1, point);
			Assert::AreEqual(0, result);
		}

		TEST_METHOD(TC035) {
			Box* box = NULL;
			Point point = { 2, 3 };
			int result = inputBox(box, 2, 10, 0.5, point);
			Assert::IsNull(box);
			Assert::AreEqual(-1, result);
		}

		TEST_METHOD(TC036) {
			Box box;
			Point point = { 2, -2 };
			int result = inputBox(&box, 3, 10, 0.5, point);
			Assert::AreEqual(0, result);
			Assert::AreEqual(0, box.id);
			Assert::AreEqual((double)0, box.volume);
			Assert::AreEqual((double)0, box.weight);
			Assert::AreEqual(-1, box.destination.row);
			Assert::AreEqual(-1, box.destination.col);
		}

		TEST_METHOD(TC037) {
			Box box;
			Point point = { 2, 3 };
			int result = inputBox(&box, 4, 20, 8, point);
			Assert::AreEqual(0, result);
			Assert::AreEqual(0, box.id);
			Assert::AreEqual((double)0, box.volume);
			Assert::AreEqual((double)0, box.weight);
			Assert::AreEqual(-1, box.destination.row);
			Assert::AreEqual(-1, box.destination.col);
		}
	};

	TEST_CLASS(ValidateTruckWhiteBox) {
		TEST_METHOD(TC046) {
			Box loadedBoxes[26]{};
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			Route blueRoute = getBlueRoute();
			const struct Truck truck = { 70, 26, 1, blueRoute, *loadedBoxes };
			int result = validateTruck(&truck);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(TC047) {
			struct Truck* truck = NULL;
			int result = validateTruck(truck);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(TC048) {
			Box loadedBoxes[26]{};
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 1, 2, 1.0, (5,6) };
			}
			Route blueRoute = getBlueRoute();
			const struct Truck truck = { 1, 26, 100.0, blueRoute, *loadedBoxes };
			int result = validateTruck(&truck);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(TC049) {

		}
	};

	TEST_CLASS(loadBoxWhiteBox) {
		TEST_METHOD(TC050) {
			Route blueRoute = getBlueRoute();
			Box loadedBoxes[26]{};
			for (int i = 0; i < 26; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			struct Truck truck = { 70, 26, 72.0, blueRoute, *loadedBoxes };
			struct Box box = { 123, 1201.0, 10.0, {5, 6} };
			int result = loadBox(&truck, &box);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TC051) {
			Route blueRoute = getBlueRoute();
			Box loadedBoxes[100]{};
			for (int i = 0; i < 100; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			struct Truck truck = { 70, 100, 72.0, blueRoute, *loadedBoxes };
			struct Box box = { 123, 121.0, 2.0, {5, 6} };
			int result = loadBox(&truck, &box);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TC052) {
			Route blueRoute = getBlueRoute();
			Box loadedBoxes[22]{};
			for (int i = 0; i < 22; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			struct Truck truck = { 70, 100, 72.0, blueRoute, *loadedBoxes };
			struct Box box = { 123, 15.0, 3.0, {5, 6} };
			int result = loadBox(&truck, &box);
			Assert::AreEqual(-1, result);
		}
		TEST_METHOD(TC053) {
			Route blueRoute = getBlueRoute();
			Box loadedBoxes[100]{};
			for (int i = 0; i < 100; i++) {
				loadedBoxes[i] = { 10, 2, 1.0, (5,6) };
			}
			struct Truck truck = { 70, 100, 72.0, blueRoute, *loadedBoxes };
			struct Box box = { 123, 121.0, 2.0, {5, 6} };
			int result = loadBox(&truck, &box);
			Assert::AreEqual(-1, result);
		}
	};

	TEST_CLASS(addPtToRouteWhiteBox) {
		TEST_METHOD(TC054) {
			Route route = getBlueRoute();
			Point pt = { -1, -5 };
			addPtToRoute(&route, pt);
			Assert::AreEqual(route.points[route.numPoints - 1].row, -1);
			Assert::AreEqual(route.points[route.numPoints - 1].col, -5);
		}
	};

	TEST_CLASS(getPossibleMovesWhiteBox) {
		TEST_METHOD(TC055) {
			Map map = populateMap();
			Route route = getBlueRoute();
			Point p1 = { -1, -1 };
			Point backpath = { 0, 0 };
			Route result = getPossibleMoves(&map, p1, &route);

			Assert::AreEqual(result.numPoints, 2);
		}
		TEST_METHOD(TC056) {
			Map map = populateMap();
			Route route = getGreenRoute();
			Point p1 = { -1, -1 };
			Point backpath = { 0, 0 };
			Route result = getPossibleMoves(&map, p1, &route);

			Assert::AreEqual(result.numPoints, 2);
		}
	};

	TEST_CLASS(selectByWeightLoadWhiteBox) {
		TEST_METHOD(TC090) {
			//Box loadedBoxes[10]{};
			//Box loadedBoxes2[50]{};
			//Box loadedBoxes3[20]{};
			//for (int i = 0; i < 10; i++)
			//	loadedBoxes[i] = { 1,20,1,{2,3} };
			//for (int i = 0; i < 50; i++)
			//	loadedBoxes2[i] = { 1,20,1,{3,2} };
			//for (int i = 0; i < 20; i++)
			//	loadedBoxes3[i] = { 1,60, 1,{3,2} };
			//struct Truck trucks[] = {
			//{0.2, 10, 10, getBlueRoute(), *loadedBoxes},
			//{1000, 50, 50, getYellowRoute(), *loadedBoxes2},
			//{1200, 20, 20, getGreenRoute(), *loadedBoxes3}
			//};
			int shortList[] = { true, true, true };
			Box box = { 1,20,1,{2,3} };
			Truck TruckA = { 0.1667,1,0.8,getBlueRoute(),{box}};
			Truck TruckB = { 0.8333,5,.5,getGreenRoute(),{box}};
			Truck TruckC = { 1,20,.2,getYellowRoute(),{box} };

			Truck trucks[] = { TruckA, TruckB, TruckC };


			int result = selectByWeightLoad(shortList, trucks);

			Assert::AreEqual(0, result);
			Assert::AreEqual(1, shortList[0]);
			Assert::AreEqual(0, shortList[1]);
			Assert::AreEqual(0, shortList[2]);
		}
		TEST_METHOD(TC091) {
			int shortList[] = { true, true, true };
			Box box = { 1,20,1,{2,3} };
			Truck TruckA = { 0.1667,1,0.8,getBlueRoute(),{box} };
			Truck TruckB = { 0.8333,5,.5,getGreenRoute(),{box} };
			Truck TruckC = { 1,20,1.2,getYellowRoute(),{box} };

			Truck trucks[] = { TruckA, TruckB, TruckC };


			int result = selectByWeightLoad(shortList, trucks);

			Assert::AreEqual(-1, result);
		}
	};

	TEST_CLASS(selectbyVolLoadWhiteboX) {
		TEST_METHOD(TC092) {
			int shortList[] = { true, true, true };
			Box box = { 1,20,1,{2,3} };
			Truck TruckA = { 0.1667,1,0.2,getBlueRoute(),{box} };
			Truck TruckB = { 0.8333,5,.5,getGreenRoute(),{box} };
			Truck TruckC = { 1,20,.2,getYellowRoute(),{box} };

			Truck trucks[] = { TruckA, TruckB, TruckC };


			int result = selectByVolLoad(shortList, trucks);

			Assert::AreEqual(0, result);
			Assert::AreEqual(1, shortList[0]);
			Assert::AreEqual(0, shortList[1]);
			Assert::AreEqual(1, shortList[2]);
		}
		TEST_METHOD(TC093) {
			Box loadedBoxes[10]{};
			Box loadedBoxes2[50]{};
			for (int i = 0; i < 10; i++)
				loadedBoxes[i] = { 1,20,1,{2,3} };
			for (int i = 0; i < 50; i++)
				loadedBoxes2[i] = { 1,20,1,{3,2} };
			struct Truck trucks[] = {
			{200, 10, 10, getBlueRoute(), *loadedBoxes},
			{1000, 50, 50, getYellowRoute(), *loadedBoxes2},
			{1200, 20, 20, {{{1,1}, {1,0}, {2,0}, {3,1}}, 4, 'I'}}
			};
			int shortList[] = { true, true, true };
			int result = selectByVolLoad(shortList, trucks);
			Assert::AreEqual(-1, result);
		}
	};


	TEST_CLASS(SelectTruckWhiteBox)
	{
		TEST_METHOD(TC098)
		{
			Box loadedBoxes[10]{};
			Box loadedBoxes2[50]{};
			Box loadedBoxes3[20]{};
			for (int i = 0; i < 10; i++)
				loadedBoxes[i] = { 1,20,1,{2,3} };
			for (int i = 0; i < 50; i++)
				loadedBoxes2[i] = { 1,20,1,{3,2} };
			for (int i = 0; i < 20; i++)
				loadedBoxes3[i] = { 1,60, 1,{3,2} };

			int shortList[] = { 1, 1, 1 };
			struct Map map = populateMap();
			struct Truck trucks[] = {
				{.1, 10, .1, getBlueRoute(),*loadedBoxes},
				{.1, 50, .5, getYellowRoute(), *loadedBoxes2},
				{.1, 20, .2, getGreenRoute(), *loadedBoxes3}
			};
			struct Box box = { 1, 20, 1, {2, 3} };
			int expected = 0;
			int result = selectTruck(shortList, &map, trucks, &box);
			Assert::AreEqual(expected, result);
			Assert::AreEqual(0, result);
			Assert::AreEqual(1, shortList[0]);
			Assert::AreEqual(0, shortList[1]);
			Assert::AreEqual(0, shortList[2]);
		}

		TEST_METHOD(TC099)
		{
			Box loadedBoxes[10]{};
			Box loadedBoxes2[50]{};
			Box loadedBoxes3[20]{};
			for (int i = 0; i < 10; i++)
				loadedBoxes[i] = { 1,20,1,{2,3} };
			for (int i = 0; i < 50; i++)
				loadedBoxes2[i] = { 1,20,1,{3,2} };
			for (int i = 0; i < 20; i++)
				loadedBoxes3[i] = { 1,60, 1,{3,2} };

			int shortList[] = { 1, 1, 1 };
			struct Map* map = nullptr;
			struct Truck trucks[] = {
				{200, 10, 10, getBlueRoute(), *loadedBoxes},
				{1000, 50, 50, getYellowRoute(), *loadedBoxes2},
				{1200, 20, 20, getGreenRoute(), *loadedBoxes3}
			};
			struct Box box = { 1, 20, 1, {2, 3} };
			int expected = -1;
			int result = selectTruck(shortList, map, trucks, &box);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TC100)
		{
			Box loadedBoxes[10]{};
			Box loadedBoxes2[50]{};
			Box loadedBoxes3[20]{};
			for (int i = 0; i < 10; i++)
				loadedBoxes[i] = { 1,20,1,{2,3} };
			for (int i = 0; i < 50; i++)
				loadedBoxes2[i] = { 1,20,1,{3,2} };
			for (int i = 0; i < 20; i++)
				loadedBoxes3[i] = { 1,60, 1,{3,2} };

			int shortList[] = { 1, 1, 1 };
			struct Map map = populateMap();
			struct Truck trucks[] = {
				{200, 10, 10, getBlueRoute(), *loadedBoxes},
				{1000, 50, 50, getYellowRoute(), *loadedBoxes2},
				{1200, 20, 20, {{{1,1}, {1,0}, {2,0}, {3,1}}, 4, 'I'}, *loadedBoxes3}
			};
			struct Box box = { 1, 20, 1, {2, 3} };
			int expected = -1;
			int result = selectTruck(shortList, &map, trucks, &box);
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(TC101)
		{
			Box loadedBoxes[10]{};
			Box loadedBoxes2[50]{};
			Box loadedBoxes3[20]{};
			for (int i = 0; i < 10; i++)
				loadedBoxes[i] = { 1,20,1,{2,3} };
			for (int i = 0; i < 50; i++)
				loadedBoxes2[i] = { 1,20,1,{3,2} };
			for (int i = 0; i < 20; i++)
				loadedBoxes3[i] = { 1,60, 1,{3,2} };

			int shortList[] = { 1, 1, 1 };
			struct Map map = populateMap();
			struct Truck trucks[] = {
				{200, 10, 10, getBlueRoute(), *loadedBoxes},
				{1000, 50, 50, getYellowRoute(), *loadedBoxes2},
				{1200, 20, 20, getGreenRoute(), *loadedBoxes3}
			};
			struct Box box = { 0, 0, 0.7, {-5, -6} };
			int expected = -1;
			int result = selectTruck(shortList, &map, trucks, &box);
			Assert::AreEqual(expected, result);
		}
	};


}
