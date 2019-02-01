/*
 * FogLAMP south service plugin
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch
 */
#include <expression.h>
#include <config_category.h>
#include <reading.h>
#include <stdlib.h>
#include <logger.h>

using namespace std;
/**
 * Constructor for the expression "sensor"
 */
SouthExpression::SouthExpression()
{
}

/**
 * Destructor for the expression "sensor"
 */
SouthExpression::~SouthExpression()
{
}

void SouthExpression::configure(ConfigCategory *config)
{
	m_minX = strtof(config->getValue("minimumX").c_str(), NULL);
	m_maxX = strtof(config->getValue("maximumX").c_str(), NULL);
	m_stepX = strtof(config->getValue("stepX").c_str(), NULL);
	setAssetName(config->getValue("asset"));
	setExpression(config->getValue("expression"));

	m_x = m_minX;

	m_symbolTable.add_variable("x", m_x);
	m_symbolTable.add_constants();
	m_expression.register_symbol_table(m_symbolTable);
	m_parser.compile(m_exprStr, m_expression);
}

/**
 * Take a reading from the expression "sensor"
 */
Reading	SouthExpression::nextValue()
{
double	y;

	y = m_expression.value();
	m_x += m_stepX;
	if (m_x > m_maxX)
	{
		m_x = m_minX;
	}
	DatapointValue value(y);
	return Reading(m_asset,new Datapoint(m_asset, value));
}
