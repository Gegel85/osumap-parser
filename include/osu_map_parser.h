#ifndef OSUMAP_PARSER_LIBRARY_H
#define OSUMAP_PARSER_LIBRARY_H

#include <stdbool.h>
#include <stddef.h>

#ifndef __OSU_GAME_MODE_HEADER_
#define __OSU_GAME_MODE_HEADER_

enum OsuGameMode {
	GAME_OSU_STANDARD,
	GAME_TAIKO,
	GAME_CATCH_THE_BEAT,
	GAME_OSU_MANIA,
	GAME_STD	= GAME_OSU_STANDARD,
	GAME_CTB	= GAME_CATCH_THE_BEAT,
	GAME_MANIA	= GAME_OSU_MANIA,
};

#endif

enum OsuHitObjectType {
	HITOBJ_CIRCLE          = 1U << 0U,
	HITOBJ_SLIDER          = 1U << 1U,
	HITOBJ_NEW_COMBO       = 1U << 2U,
	HITOBJ_SPINNER         = 1U << 3U,
	HITOBJ_NBR1            = 1U << 4U,
	HITOBJ_NBR2            = 1U << 5U,
	HITOBJ_NBR3            = 1U << 6U,
	HITOBJ_COLOR_SKIP_NBR  = HITOBJ_NBR1 | HITOBJ_NBR2 | HITOBJ_NBR3,
	HITOBJ_MANIA_LONG_NOTE = 1U << 7U,
};

enum OsuHitSounds {
	HIT_NORMAL  = 1U << 0U,
	HIT_WHISTLE = 1U << 1U,
	HIT_FINISH  = 1U << 2U,
	HIT_CLAP    = 1U << 3U,
};

typedef struct OsuLongVector {
	long	x;
	long	y;
} OsuLongVector;

typedef struct OsuMap_integerArray {
	size_t		length;
	unsigned int	*content;
} OsuMap_unsignedIntegerArray;

typedef struct OsuMap_generalInfos {
	char		*audioFileName;
	long		audioLeadIn;
	unsigned long	previewTime;
	enum OsuGameMode	mode;
	bool		countdown;
	char		*hitSoundsSampleSet;
	double		stackLeniency;
	bool		letterBoxInBreaks;
	bool		widescreenStoryboard;
	bool		storyFireInFront;
	bool		specialStyle;
	bool		epilepsyWarning;
	bool		useSkinSprites;
} OsuMap_generalInfos;

typedef struct OsuMap_editorInfos {
	OsuMap_unsignedIntegerArray	bookmarks;
	double				distanceSpacing;
	double				beatDivision;
	int				gridSize;
	double				timeLineZoom;
} OsuMap_editorInfos;

typedef struct OsuMap_metaData {
	char		*title;
	char		*unicodeTitle;
	char		*artist;
	char		*artistUnicode;
	char		*creator;
	char		*difficulty;
	char		*musicOrigin;
	char		**tags;
	unsigned long	beatmapID;
	unsigned long	beatmapSetID;
} OsuMap_metaData;

typedef struct OsuMap_difficultyInfos {
	double	hpDrainRate;
	double	circleSize;
	double	overallDifficulty;
	double	approachRate;
	double	sliderMultiplayer;
	double	sliderTickRate;
} OsuMap_difficultyInfos;

typedef struct OsuMap_storyboardEvent {
	int i; // Just so that MSVC is happy.
	// TODO: Create storyboard struct.
} OsuMap_storyboardEvent;

typedef struct OsuMap_storyboardArray {
	size_t			length;
	OsuMap_storyboardEvent	*content;
} OsuMap_storyboardArray;

typedef struct OsuMap_timingPointEvent {
	unsigned long	timeToHappen;
	double		millisecondsPerBeat;
	unsigned short	beatPerMeasure;
	long		sampleSet;
	long		sampleIndex;
	char		volume;
	bool		inherited;

} OsuMap_timingPointEvent;

typedef struct OsuMap_timingPointArray {
	size_t			length;
	OsuMap_timingPointEvent	*content;
} OsuMap_timingPointArray;

typedef struct OsuMap_color {
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
} OsuMap_color;

typedef struct OsuMap_colorArray {
	size_t		length;
	OsuMap_color	*content;
} OsuMap_colorArray;

typedef struct OsuMap_sampleSet {
	char	sampleSet;
	char	additionsSampleSet;
} OsuMap_sampleSet;

typedef struct OsuMapCategory {
	char	*name;
	char	**lines;
} OsuMapCategory;

typedef struct OsuMap_hitObjectAddition {
	OsuMap_sampleSet	sampleSet;
	long			customIndex;
	char			sampleVolume;
	char			*fileName;
} OsuMap_hitObjectAddition;

typedef struct OsuLongVectorArray {
	size_t		length;
	OsuLongVector	*content;
} OsuLongVectorArray;

typedef struct OsuMap_hitObjectSliderInfos {
	char			type;
	OsuLongVectorArray	curvePoints;
	unsigned int		nbOfRepeats;
	double			pixelLength;
	unsigned char		*edgeHitsounds;
	OsuMap_sampleSet	*edgeAdditions;
} OsuMap_hitObjectSliderInfos;

typedef struct OsuMap_hitObject {
	OsuLongVector			position;
	unsigned long			timeToAppear;
	unsigned char			type;
	unsigned char			hitSound;
	void				*additionalInfos;
	OsuMap_hitObjectAddition	extra;
} OsuMap_hitObject;

typedef struct OsuMap_hitObjectArray {
	size_t			length;
	OsuMap_hitObject	*content;
} OsuMap_hitObjectArray;

typedef struct OsuMap_StoryBoard {
	char			*backgroundPath;
	char			*videoPath;
	OsuMap_storyboardArray	storyboardEvents;
} OsuMap_storyBoard;

typedef struct OsuMap {
	char			*__str;
	char			*error;
	unsigned int		fileVersion;
	OsuMap_generalInfos	generalInfos;
	OsuMap_editorInfos	editorInfos;
	OsuMap_metaData		metaData;
	OsuMap_difficultyInfos	difficulty;
	OsuLongVector		*breaks;
	OsuMap_storyBoard	storyBoard;
	OsuMap_timingPointArray	timingPoints;
	OsuMap_colorArray	colors;
	OsuMap_hitObjectArray	hitObjects;
} OsuMap;

OsuMap	OsuMap_parseMapString(const char *string);
OsuMap	OsuMap_parseMapFile(const char *path);
void OsuMap_destroy(OsuMap *map);

#endif //OSUMAP_PARSER_LIBRARY_H
