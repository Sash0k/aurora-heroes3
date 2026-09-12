/*
 * IScreenHandler.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../../lib/Point.h"

VCMI_LIB_NAMESPACE_BEGIN
class Rect;
VCMI_LIB_NAMESPACE_END

class IScreenHandler
{
public:
	virtual ~IScreenHandler() = default;

	/// Updates window state after fullscreen state has been changed in settings
	virtual void onScreenResize() = 0;

	/// De-initializes window state
	virtual void close() = 0;

	/// Fills screen with black color, erasing any existing content
	virtual void clearScreen() = 0;

	/// Returns list of resolutions supported by current screen
	virtual std::vector<Point> getSupportedResolutions() const = 0;

	/// Returns <min, max> range of possible values for screen scaling percentage
	virtual std::tuple<int, int> getSupportedScalingRange() const = 0;

	/// Converts provided rect from logical coordinates into coordinates within window, accounting for scaling and viewport
	virtual Rect convertLogicalPointsToWindow(const Rect & input) const = 0;

	/// Dimensions of render output
	virtual Point getRenderResolution() const = 0;

	/// Dimensions of logical output. Can be different if scaling is used
	virtual Point getLogicalResolution() const = 0;

	virtual int getInterfaceScalingPercentage() const = 0;

	virtual int getScalingFactor() const = 0;

	/// Window has focus
	virtual bool hasFocus() = 0;

#ifdef VCMI_AURORAOS
	/// [auroraos] Applies new display orientation: sets wayland buffer transform and
	/// updates internal rotation state used for rendering and input coordinates conversion
	virtual void setScreenOrientation(int orientation) = 0;

	/// [auroraos] Renders main screen texture onto renderer applying software rotation and scaling
	virtual void renderScreenTexture() = 0;

	/// [auroraos] Converts point in window (buffer) coordinates into point on main surface
	virtual Point convertWindowToSurface(const Point & windowPoint) const = 0;

	/// [auroraos] Converts offset in window coordinates into offset on main surface (rotation and scaling, no offset)
	virtual Point convertWindowDeltaToSurface(const Point & windowDelta) const = 0;

	/// [auroraos] Converts point on main surface into window coordinates, e.g. for software cursor rendering
	virtual Point convertSurfaceToWindow(const Point & surfacePoint) const = 0;

	/// [auroraos] Current rotation angle of screen content in degrees (0, 90, 180 or 270)
	virtual double getScreenRotation() const = 0;

	/// [auroraos] Dimensions of game window (buffer) in pixels
	virtual Point getWindowDimensions() const = 0;
#endif
};
