/****************************************************************************
**
** Clone of Sparkle's SUStandardVersionComparator.m, so here's original author's
** copyright too:
**
** Copyright 2007 Andy Matuschak. All rights reserved.
** Everything's the same except for TypeOfCharacter()
** (because who knows how Foundation does isdigit() and such.)
**
**
** Copyright (C) 2015 Yash Pal, Speedovation
** Copyright (C) 2012 Linas Valiukas
**
** Contact: Speedovation Lab (info@speedovation.com)
**
** KineticWing Auto Updater
** http:// kineticwing.com
** This file is part of the KiWi Editor (IDE)
**
** Author: Yash Pal, Linas Valiukas
** License : Apache License 2.0
**
** All rights are reserved.
*/

#ifndef VERSIONCOMPARATOR_H
#define VERSIONCOMPARATOR_H

#include <iosfwd>
#include <vector>


class VersionComparator
{
public:

	typedef enum {
		kSame = 0,
		kDescending = 1,
		kAscending = -1
	} ComparatorResult;

	static ComparatorResult CompareVersions(std::string versionA,
											std::string versionB);

private:

	VersionComparator();

	typedef enum {
		kNumberType,
		kStringType,
		kSeparatorType
	} CharacterType;

	static CharacterType TypeOfCharacter(std::string character);
	static std::vector<std::string> SplitVersionString(std::string version);

};

#endif // VERSIONCOMPARATOR_H
