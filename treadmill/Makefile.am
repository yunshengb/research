ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I$(top_srcdir)/..

noinst_LIBRARIES = libtreadmill.a

libtreadmill_a_SOURCES = \
	Connection.h \
	Histogram.h \
	Request.h \
	RandomEngine.h \
	Scheduler.h \
	Statistic.h \
	ContinuousStatistic.h \
	CounterStatistic.h \
	StatisticsManager.h \
	Treadmill.h \
	Util.h \
	Worker.h \
	Workload.h \
	Histogram.cpp \
	RandomEngine.cpp \
	Scheduler.cpp \
	Treadmill.cpp \
	ContinuousStatistic.cpp \
	CounterStatistic.cpp \
	StatisticsManager.cpp \
	Util.cpp

bin_PROGRAMS = \
	treadmill_lucida

treadmill_lucida_SOURCES = \
	services/lucida/Connection.h \
	services/lucida/MemcachedService.h \
	services/lucida/Request.h \
	services/lucida/Treadmill.cpp \
	services/lucida/Workload.h

treadmill_lucida_LDADD = \
	libtreadmill.a \
	-lcurl
