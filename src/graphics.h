/*
Copyright (C) 2015 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "kerneltypes.h"
#include "sys_window_struct.h"


int graphics_width();
int graphics_height();

/**
 * @brief Sets bounds for restricted drawing
 * @details This will restrict all drawing to the given area of the screen.
 * Drawing outside this area will have no effect
 *
 * @param x The x position of the top left corner of the bounding box
 * @param y The y position of the top left corner of the bounding box
 * @param width The width of the bounding box
 * @param height The height of the bounding box
 */
void graphics_set_bounds(int x, int y, int width, int height);

/**
 * @brief Clears the graphics drawing restrictions
 * @details This removes any restriction on drawing area that was added
 * by graphics_set_bounds
 */
void graphics_clear_bounds();

/**
 * @brief Draws a line on the display from (x1, y1) to (x2, y2)
 * @details Order of points does not matter. Points outside of display will be rounded to the closest edge
 *
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @param c: color of line
 * @param mouse_draw: bool that sets whether the mouse is drawing (basically, whether to use plot_pixel or not)
 * @return
 */
void graphics_line(int x1, int y1, int x2, int y2, struct graphics_color c, bool mouse_draw);
/**
 * @brief Draws a curve with given radius and range
 * @details This draws a curve from start_t to end_t with
 * a given radius. The curve will be circular as opposed to elliptical.
 * Angles should be given on a unit circle ranging from 0 to 2PI
 *
 * @param x The x coordinate of the center of the arc
 * @param y The y coordinate of the center of the arc
 * @param r The radius of the arc
 * @param start_theta The starting angle of the arc, in radians
 * @param end_theta The ending angle of the arc, in radians
 * @param graphics_color The color to draw in
 */
void graphics_arc(int x, int y, double r, double start_theta, double end_theta,
                  struct graphics_color c);

/**
 * @brief Draws a circle centered at given point
 * @details Draws an arc from 0 to 2PI centered at x, y in the given color
 * with a radius of r
 *
 * @param x The x coordinate of the center
 * @param y The y coordinate of the center
 * @param r The radius of the circle
 * @param graphics_color The color to draw in
 */
void graphics_circle(int x, int y, double r, struct graphics_color c);
void graphics_rect(int x, int y, int w, int h, struct graphics_color c);
void graphics_clear(struct graphics_color c);
void graphics_char(int x, int y, char ch, struct graphics_color fgcolor,
                   struct graphics_color bgcolor);
void graphics_bitmap(int x, int y, int width, int height, uint8_t * data,
                     struct graphics_color fgcolor,
                     struct graphics_color bgcolor);

/**
 * @brief Copies part of video buffer into a color buffer.
 * @details Copies a rectangular region of the video into a buffer of graphics_color. It does checking for the region size exceeding the buffer size (provided as a param).
 *
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param width Width of the region.
 * @param height Height of the region.
 * @param buffer Pointer to a struct graphics_color buffer.
 * @param buf_size Size of the buffer.
 */
void graphics_copy_to_color_buffer(int x, int y, int width, int height, struct graphics_color *buffer, int buf_size);

/**
 * @brief Copies a color buffer into the video buffer.
 * @details Copies a buffer of graphics_color into a rectangular region of the video. It does checking for the region size exceeding the buffer size (provided as a param).
 *
 * @param x Starting x coordinate.
 * @param y Starting y coordinate.
 * @param width Width of the region.
 * @param height Height of the region.
 * @param buffer Pointer to a struct graphics_color buffer.
 * @param buf_size Size of the buffer.
 */
void graphics_copy_from_color_buffer(int x, int y, int width, int height, struct graphics_color *buffer, int buf_size);

/**
 * @brief Draws the mouse on the screen
 * @details This copies the old mouse_draw_buffer back into the video buffer and then copies the new mouse region from the video buffer into mouse_draw_buffer. It then draws the mouse (a cross) on the screen. graphics_mouse does not use plot_pixel because of mouse_buffer checking. This should be used only when the mouse position changes. Otherwise, it wastes computation.
 */
void graphics_mouse();

#endif

