/*
 * Fledge south plugin.
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch
 */
#include <expression.h>
#include <plugin_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string>
#include <logger.h>
#include <plugin_exception.h>
#include <config_category.h>
#include <version.h>
#include <mutex>

using namespace std;

#define PLUGIN_NAME "Expression"
#define CONFIG	"{\"plugin\" : { \"description\" : \"" PLUGIN_NAME " C south plugin\", " \
			"\"type\" : \"string\", \"default\" : \"" PLUGIN_NAME "\", \"readonly\": \"true\" }, " \
		"\"asset\" : { \"description\" : \"Asset name\", " \
			"\"type\" : \"string\", \"default\" : \"Expression\", " \
			"\"order\": \"1\", \"displayName\": \"Asset Name\" }," \
		"\"expression\" : { \"description\" : \"Expression to evaluate\", " \
			"\"type\" : \"string\", \"default\" : \"clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)\", " \
			"\"order\": \"2\", \"displayName\": \"Expression\" }," \
		"\"minimumX\" : { \"description\" : \"Minimum value of x\", " \
			"\"type\" : \"float\", \"default\" : \"-5\", " \
			"\"order\": \"3\", \"displayName\": \"Minimum Value\" }," \
		"\"maximumX\" : { \"description\" : \"Maximum value of x\", " \
			"\"type\" : \"float\", \"default\" : \"5\", " \
			"\"order\": \"4\", \"displayName\": \"Maximum Value\" }," \
		"\"stepX\" : { \"description\" : \"Step value of x\", " \
			"\"type\" : \"float\", \"default\" : \"0.001\", " \
			"\"order\": \"5\", \"displayName\": \"Step Value\" }" \
		"} "
		  
/**
 * The Expression plugin interface
 */
extern "C" {

/**
 * The plugin information structure
 */
static PLUGIN_INFORMATION info = {
	PLUGIN_NAME,              // Name
	VERSION,                  // Version
	0,    			  // Flags
	PLUGIN_TYPE_SOUTH,        // Type
	"1.0.0",                  // Interface version
	CONFIG                    // Default configuration
};

static mutex exp_mutex;

/**
 * Return the information about this plugin
 */
PLUGIN_INFORMATION *plugin_info()
{
	return &info;
}

/**
 * Initialise the plugin, called to get the plugin handle
 */
PLUGIN_HANDLE plugin_init(ConfigCategory *config)
{
SouthExpression *expression = new SouthExpression();

	expression->configure(config);

	return (PLUGIN_HANDLE)expression;
}

/**
 * Start the Async handling for the plugin
 */
void plugin_start(PLUGIN_HANDLE *handle)
{
}

/**
 * Poll for a plugin reading
 */
Reading plugin_poll(PLUGIN_HANDLE *handle)
{
SouthExpression *expression = (SouthExpression *)handle;

	lock_guard<mutex> guard(exp_mutex);
	return expression->nextValue();
}

/**
 * Reconfigure the plugin
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, string& newConfig)
{
ConfigCategory	config("expression", newConfig);
SouthExpression		*expression = (SouthExpression *)*handle;

	expression->configure(&config);
}

/**
 * Shutdown the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE *handle)
{
SouthExpression *expression = (SouthExpression *)handle;

	lock_guard<mutex> guard(exp_mutex);
	delete expression;
}
};
