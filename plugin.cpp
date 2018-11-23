/*
 * FogLAMP south plugin.
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

using namespace std;

#define PLUGIN_NAME "Expression"
#define CONFIG	"{\"plugin\" : { \"description\" : \"" PLUGIN_NAME " C south plugin\", " \
			"\"type\" : \"string\", \"default\" : \"" PLUGIN_NAME "\" }, " \
		"\"asset\" : { \"description\" : \"Asset name\", " \
			"\"type\" : \"string\", \"default\" : \"Expression\" }," \
		"\"expression\" : { \"description\" : \"Expression to evaluate\", " \
			"\"type\" : \"string\", \"default\" : \"clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)\" }," \
		"\"minimumX\" : { \"description\" : \"Minimum value of x\", " \
			"\"type\" : \"float\", \"default\" : \"-5\" }," \
		"\"maximumX\" : { \"description\" : \"Maximum value of x\", " \
			"\"type\" : \"float\", \"default\" : \"5\" }," \
		"\"stepX\" : { \"description\" : \"Step value of x\", " \
			"\"type\" : \"float\", \"default\" : \"0.001\" }" \
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
	"1.0.0",                  // Version
	0,    			  // Flags
	PLUGIN_TYPE_SOUTH,        // Type
	"1.0.0",                  // Interface version
	CONFIG                    // Default configuration
};

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
Expression *expression = new Expression();

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
Expression *expression = (Expression *)handle;

	return expression->nextValue();
}

/**
 * Reconfigure the plugin
 */
void plugin_reconfigure(PLUGIN_HANDLE *handle, string& newConfig)
{
ConfigCategory	config("expression", newConfig);
Expression		*expression = (Expression *)handle;

	expression->configure(&config);
}

/**
 * Shutdown the plugin
 */
void plugin_shutdown(PLUGIN_HANDLE *handle)
{
Expression *expression = (Expression *)handle;

	delete expression;
}
};
