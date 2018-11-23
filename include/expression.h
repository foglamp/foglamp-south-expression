#ifndef _EXPRESSION_H
#define _EXPRESSION_H
/*
 * FogLAMP south service plugin
 *
 * Copyright (c) 2018 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch
 */
#include <reading.h>
#include <config_category.h>
#include <exprtk.hpp>


class Expression {
	public:
		Expression();
		~Expression();
		Reading		nextValue();
	void	setAssetName(const std::string& assetName)
		{
			m_asset = assetName;
		}
	void	setExpression(const std::string& expression)
		{
			m_exprStr = expression;
		}
	void	configure(ConfigCategory *config);

	private:
		typedef exprtk::symbol_table<double>	symbol_table_t;
		typedef exprtk::expression<double>	expression_t;
		typedef exprtk::parser<double>		parser_t;

		double		m_minX;
		double		m_maxX;
		double		m_stepX;
		double		m_x;
		std::string	m_asset;
		std::string	m_exprStr;

		expression_t	m_expression;
		parser_t	m_parser;
		symbol_table_t	m_symbolTable;
};
#endif
