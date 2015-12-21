/*
     File:       CarbonCore/Finder.h
 
     Contains:   Finder flags and container types.
 
     Version:    CarbonCore-960.24~1
 
     Copyright:  � 1990-2008 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FINDER__
#define __FINDER__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma pack(push, 2)

/* Creator and type of clipping files */
enum {
  kClippingCreator              = 'drag',
  kClippingPictureType          = 'clpp',
  kClippingTextType             = 'clpt',
  kClippingSoundType            = 'clps',
  kClippingUnknownType          = 'clpu'
};


/* Creator and type of Internet Location files */
enum {
  kInternetLocationCreator      = 'drag',
  kInternetLocationHTTP         = 'ilht',
  kInternetLocationFTP          = 'ilft',
  kInternetLocationFile         = 'ilfi',
  kInternetLocationMail         = 'ilma',
  kInternetLocationNNTP         = 'ilnw',
  kInternetLocationAFP          = 'ilaf',
  kInternetLocationAppleTalk    = 'ilat',
  kInternetLocationNSL          = 'ilns',
  kInternetLocationGeneric      = 'ilge'
};



enum {
  kCustomIconResource           = -16455 /* Custom icon family resource ID */
};

/* In order to specify any of the information described in the */
/* CustomBadgeResource data structure you must clear the kExtendedFlagsAreInvalid */
/* and set kExtendedFlagHasCustomBadge of the FXInfo.fdXFlags or DXInfo.frXFlags field, */
/* and add a resource of type kCustomBadgeResourceType and ID kCustomBadgeResourceID to */
/* the file or to the "Icon/n" file for a folder */
enum {
  kCustomBadgeResourceType      = 'badg',
  kCustomBadgeResourceID        = kCustomIconResource,
  kCustomBadgeResourceVersion   = 0
};

struct CustomBadgeResource {
  SInt16              version;                /* This is version kCustomBadgeResourceVersion*/
  SInt16              customBadgeResourceID;  /* If not 0, the ID of a resource to use on top*/
                                              /* of the icon for this file or folder*/
  OSType              customBadgeType;        /* If not 0, the type and creator of an icon*/
  OSType              customBadgeCreator;     /* to use on top of the icon*/
  OSType              windowBadgeType;        /* If not 0, the type and creator of an icon*/
  OSType              windowBadgeCreator;     /* to display in the header of the window for this */
                                              /* file or folder*/
  OSType              overrideType;           /* If not 0, the type and creator of an icon to*/
  OSType              overrideCreator;        /* use INSTEAD of the icon for this file or folder*/
};
typedef struct CustomBadgeResource      CustomBadgeResource;
typedef CustomBadgeResource *           CustomBadgeResourcePtr;
typedef CustomBadgeResourcePtr *        CustomBadgeResourceHandle;
/* You can specify routing information for a file by including a 'rout' 0 
    resource in it and setting the kExtendedFlagHasRoutingInfo bit in the extended 
    Finder flags. 
    The 'rout' resource is an array of RoutingResourceEntry. Each entry is considered
    in turn. The first matching entry is used.
    If the creator and fileType match the file being dropped and targetFolder match
    the folder ID of the folder being dropped onto, then the file is rerouted 
    into the specified destination folder.
    The only target folder currently supported is the system folder, 
    kSystemFolderType = 'macs'.
*/
enum {
  kRoutingResourceType          = 'rout',
  kRoutingResourceID            = 0
};

struct RoutingResourceEntry {
  OSType              creator;                /* Use '****' or 0 to match any creator */
  OSType              fileType;               /* Use '****' or 0 to match any file type */
  OSType              targetFolder;           /* Folder ID of the folder this file was dropped onto */
  OSType              destinationFolder;      /* Folder that the source will be routed to */
  OSType              reservedField;          /* Set to 0 */
};
typedef struct RoutingResourceEntry     RoutingResourceEntry;
typedef RoutingResourceEntry *          RoutingResourcePtr;
typedef RoutingResourcePtr *            RoutingResourceHandle;

/* Types for special container aliases */
enum {
  kContainerFolderAliasType     = 'fdrp', /* type for folder aliases */
  kContainerTrashAliasType      = 'trsh', /* type for trash folder aliases */
  kContainerHardDiskAliasType   = 'hdsk', /* type for hard disk aliases */
  kContainerFloppyAliasType     = 'flpy', /* type for floppy aliases */
  kContainerServerAliasType     = 'srvr', /* type for server aliases */
  kApplicationAliasType         = 'adrp', /* type for application aliases */
  kContainerAliasType           = 'drop', /* type for all other containers */
  kDesktopPrinterAliasType      = 'dtpa', /* type for Desktop Printer alias */
  kContainerCDROMAliasType      = 'cddr', /* type for CD-ROM alias */
  kApplicationCPAliasType       = 'acdp', /* type for application control panel alias */
  kApplicationDAAliasType       = 'addp', /* type for application DA alias */
  kPackageAliasType             = 'fpka', /* type for plain package alias */
  kAppPackageAliasType          = 'fapa' /* type for application package alias */
};

/* Types for Special folder aliases */
enum {
  kSystemFolderAliasType        = 'fasy',
  kAppleMenuFolderAliasType     = 'faam',
  kStartupFolderAliasType       = 'fast',
  kPrintMonitorDocsFolderAliasType = 'fapn',
  kPreferencesFolderAliasType   = 'fapf',
  kControlPanelFolderAliasType  = 'fact',
  kExtensionFolderAliasType     = 'faex'
};

/* Types for AppleShare folder aliases */
enum {
  kExportedFolderAliasType      = 'faet',
  kDropFolderAliasType          = 'fadr',
  kSharedFolderAliasType        = 'fash',
  kMountedFolderAliasType       = 'famn'
};

/* Finder flags (finderFlags, fdFlags and frFlags) */
/* Any flag reserved or not specified should be set to 0. */
/* If a flag applies to a file, but not to a folder, make sure to check */
/* that the item is not a folder by checking ((ParamBlockRec.ioFlAttrib & ioDirMask) == 0) */
enum {
  kIsOnDesk                     = 0x0001, /* Files and folders (System 6) */
  kColor                        = 0x000E, /* Files and folders */
                                        /* bit 0x0020 was kRequireSwitchLaunch, but is now reserved for future use*/
  kIsShared                     = 0x0040, /* Files only (Applications only) */
                                        /* If clear, the application needs to write to */
                                        /* its resource fork, and therefore cannot be */
                                        /* shared on a server */
  kHasNoINITs                   = 0x0080, /* Files only (Extensions/Control Panels only) */
                                        /* This file contains no INIT resource */
  kHasBeenInited                = 0x0100, /* Files only */
                                        /* Clear if the file contains desktop database */
                                        /* resources ('BNDL', 'FREF', 'open', 'kind'...) */
                                        /* that have not been added yet. Set only by the Finder */
                                        /* Reserved for folders - make sure this bit is cleared for folders */
                                        /* bit 0x0200 was the letter bit for AOCE, but is now reserved for future use */
  kHasCustomIcon                = 0x0400, /* Files and folders */
  kIsStationery                 = 0x0800, /* Files only */
  kNameLocked                   = 0x1000, /* Files and folders */
  kHasBundle                    = 0x2000, /* Files and folders */
                                        /* Indicates that a file has a BNDL resource */
                                        /* Indicates that a folder is displayed as a package */
  kIsInvisible                  = 0x4000, /* Files and folders */
  kIsAlias                      = 0x8000 /* Files only */
};

/* Obsolete. Use names defined above. */
enum {
  fOnDesk                       = kIsOnDesk,
  fHasBundle                    = kHasBundle,
  fInvisible                    = kIsInvisible
};

/* Obsolete */
enum {
  fTrash                        = -3,
  fDesktop                      = -2,
  fDisk                         = 0
};

#if OLDROUTINENAMES
enum {
  kIsStationary                 = kIsStationery
};

#endif  /* OLDROUTINENAMES */

/* Extended flags (extendedFinderFlags, fdXFlags and frXFlags) */
/* Any flag not specified should be set to 0. */
enum {
  kExtendedFlagsAreInvalid      = 0x8000, /* If set the other extended flags are ignored */
  kExtendedFlagHasCustomBadge   = 0x0100, /* Set if the file or folder has a badge resource */
  kExtendedFlagObjectIsBusy     = 0x0080, /* Set if the object is marked as busy/incomplete */
  kExtendedFlagHasRoutingInfo   = 0x0004 /* Set if the file contains routing info resource */
};



/* Use a filetype in this range to indicate that a file is temporarily busy */
/* (while it is being downloaded or installed, for example).  This prevents */
/* Finder 8.5 and later from trying to change the item's attributes before it */
/* is fully created. -- If you provide a series of 'BNDL' icons for your creator */
/* and some of these filetypes, you can achieve limited icon animation while */
/* the file creation progresses. */
enum {
  kFirstMagicBusyFiletype       = 'bzy ',
  kLastMagicBusyFiletype        = 'bzy?'
};

/* Use this date as a file's or folder's creation date to indicate that it is */
/* temporarily busy (while it is being downloaded or installed, for example). */
/* This prevents Finder from trying to change the item's attributes before it */
/* is fully created (Finder 8.5 and 8.6 check file creation dates; later Finders */
/* may check folder creation dates as well). */
enum {
  kMagicBusyCreationDate        = 0x4F3AFDB0
};


/*------------------------------------------------------------------------*/
/*
   The following data structures are binary compatible with FInfo, DInfo,
   FXInfo and DXInfo but represent the Mac OS 8 semantic of the fields.
   Use these data structures preferably to FInfo, etc...
*/
/*------------------------------------------------------------------------*/

struct FileInfo {
  OSType              fileType;               /* The type of the file */
  OSType              fileCreator;            /* The file's creator */
  UInt16              finderFlags;            /* ex: kHasBundle, kIsInvisible... */
  Point               location;               /* File's location in the folder */
                                              /* If set to {0, 0}, the Finder will place the item automatically */
  UInt16              reservedField;          /* (set to 0) */
};
typedef struct FileInfo                 FileInfo;
struct FolderInfo {
  Rect                windowBounds;           /* The position and dimension of the folder's window */
  UInt16              finderFlags;            /* ex. kIsInvisible, kNameLocked, etc.*/
  Point               location;               /* Folder's location in the parent folder */
                                              /* If set to {0, 0}, the Finder will place the item automatically */
  UInt16              reservedField;          /* (set to 0) */
};
typedef struct FolderInfo               FolderInfo;
struct ExtendedFileInfo {
  SInt16              reserved1[4];           /* Reserved (set to 0) */
  UInt16              extendedFinderFlags;    /* Extended flags (custom badge, routing info...) */
  SInt16              reserved2;              /* Reserved (set to 0). Comment ID if high-bit is clear */
  SInt32              putAwayFolderID;        /* Put away folder ID */
};
typedef struct ExtendedFileInfo         ExtendedFileInfo;
struct ExtendedFolderInfo {
  Point               scrollPosition;         /* Scroll position (for icon views) */
  SInt32              reserved1;              /* Reserved (set to 0) */
  UInt16              extendedFinderFlags;    /* Extended flags (custom badge, routing info...) */
  SInt16              reserved2;              /* Reserved (set to 0). Comment ID if high-bit is clear */
  SInt32              putAwayFolderID;        /* Put away folder ID */
};
typedef struct ExtendedFolderInfo       ExtendedFolderInfo;
/*------------------------------------------------------------------------*/
/*
   The following data structures are here for compatibility.
   Use the new data structures replacing them if possible (i.e. FileInfo 
   instead of FInfo, etc...)
*/
/*------------------------------------------------------------------------*/
/* File info */
/*
     IMPORTANT:
     In MacOS 8, the fdFldr field has become reserved for the Finder.
*/
struct FInfo {
  OSType              fdType;                 /* The type of the file */
  OSType              fdCreator;              /* The file's creator */
  UInt16              fdFlags;                /* Flags ex. kHasBundle, kIsInvisible, etc. */
  Point               fdLocation;             /* File's location in folder. */
                                              /* If set to {0, 0}, the Finder will place the item automatically */
  SInt16              fdFldr;                 /* Reserved (set to 0) */
};
typedef struct FInfo                    FInfo;
/* Extended file info */
/*
     IMPORTANT:
     In MacOS 8, the fdIconID and fdComment fields were changed
     to become reserved fields for the Finder.
     The fdScript has become an extended flag.
*/
struct FXInfo {
  SInt16              fdIconID;               /* Reserved (set to 0) */
  SInt16              fdReserved[3];          /* Reserved (set to 0) */
  SInt8               fdScript;               /* Extended flags. Script code if high-bit is set */
  SInt8               fdXFlags;               /* Extended flags */
  SInt16              fdComment;              /* Reserved (set to 0). Comment ID if high-bit is clear */
  SInt32              fdPutAway;              /* Put away folder ID */
};
typedef struct FXInfo                   FXInfo;
/* Folder info */
/*
     IMPORTANT:
     In MacOS 8, the frView field was changed to become reserved 
     field for the Finder.
*/
struct DInfo {
  Rect                frRect;                 /* Folder's window bounds */
  UInt16              frFlags;                /* Flags ex. kIsInvisible, kNameLocked, etc.*/
  Point               frLocation;             /* Folder's location in parent folder */
                                              /* If set to {0, 0}, the Finder will place the item automatically */
  SInt16              frView;                 /* Reserved (set to 0) */
};
typedef struct DInfo                    DInfo;
/* Extended folder info */
/*
     IMPORTANT:
     In MacOS 8, the frOpenChain and frComment fields were changed
     to become reserved fields for the Finder.
     The frScript has become an extended flag.
*/
struct DXInfo {
  Point               frScroll;               /* Scroll position */
  SInt32              frOpenChain;            /* Reserved (set to 0) */
  SInt8               frScript;               /* Extended flags. Script code if high-bit is set */
  SInt8               frXFlags;               /* Extended flags */
  SInt16              frComment;              /* Reserved (set to 0). Comment ID if high-bit is clear */
  SInt32              frPutAway;              /* Put away folder ID */
};
typedef struct DXInfo                   DXInfo;
/* ControlPanelDefProcPtr and cdev constants have all been moved to Processes.i*/

#pragma pack(pop)


#endif /* __FINDER__ */

