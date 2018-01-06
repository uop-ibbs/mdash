# $Id: CMakeLists.txt 112 2017-08-15 15:02:01Z dw $

message("-- Configuring wxFreeChart")

set(sources
	areadraw.cpp
	art.cpp
	axisplot.cpp
	chart.cpp
	chartpanel.cpp
	chartsplitpanel.cpp
	colorscheme.cpp
	dataset.cpp
	legend.cpp
	marker.cpp
	multiplot.cpp
	plot.cpp
	renderer.cpp
	symbol.cpp
	axis/axis.cpp
	axis/categoryaxis.cpp
	axis/compdateaxis.cpp
	axis/dateaxis.cpp
	axis/labelaxis.cpp
	axis/logarithmicnumberaxis.cpp
	axis/numberaxis.cpp
	bars/barplot.cpp
	bars/barrenderer.cpp
	category/categorydataset.cpp
	category/categorysimpledataset.cpp
	gantt/ganttdataset.cpp
	gantt/ganttplot.cpp
	gantt/ganttrenderer.cpp
	gantt/ganttsimpledataset.cpp
	ohlc/ohlcbarrenderer.cpp
	ohlc/ohlccandlestickrenderer.cpp
	ohlc/ohlcdataset.cpp
	ohlc/ohlcplot.cpp
	ohlc/ohlcrenderer.cpp
	pie/pieplot.cpp
	xy/vectordataset.cpp
	xy/xyarearenderer.cpp
	xy/xydataset.cpp
	xy/xydynamicdataset.cpp
	xy/xyhistorenderer.cpp
	xy/xylinerenderer.cpp
	xy/xyplot.cpp
	xy/xyrenderer.cpp
	xy/xysimpledataset.cpp
	xy/functions/polynom.cpp
	xy/functions/sinefunction.cpp
	xyz/bubbleplot.cpp
	xyz/xyzdataset.cpp
	xyz/xyzrenderer.cpp
)

add_library(wxfreechart ${sources})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(wxWidgets_EXCLUDE_COMMON_LIBRARIES TRUE)
endif()

find_package(wxWidgets REQUIRED adv base core html)
include(${wxWidgets_USE_FILE})

include_directories(../include)
