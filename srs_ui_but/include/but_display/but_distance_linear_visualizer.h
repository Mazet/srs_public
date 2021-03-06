/******************************************************************************
 * \file
 *
 * $Id: but_distance_linear_visualizer.h 556 2012-04-11 16:10:40Z xlokaj03 $
 *
 * Copyright (C) Brno University of Technology
 *
 * This file is part of software developed by dcgm-robotics@FIT group.
 *
 * Author: Tomas Lokaj (xlokaj03@stud.fit.vutbr.cz)
 * Supervised by: Michal Spanel (spanel@fit.vutbr.cz)
 * Date: 11/04/2012
 * 
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUT_DISTANCE_LINEAR_VISUALIZER_H_
#define BUT_DISTANCE_LINEAR_VISUALIZER_H_

#include <rviz/display.h>
#include <rviz/view_controller.h>
#include "rviz/properties/forwards.h"
#include "rviz/properties/property.h"
#include "rviz/properties/edit_enum_property.h"
#include "rviz/properties/property_manager.h"
#include <rviz/visualization_manager.h>
#include <rviz/frame_manager.h>
#include "rviz/helpers/color.h"
#include <rviz/render_panel.h>
#include <rviz/window_manager_interface.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreMaterial.h>
#include <OGRE/OgreMaterialManager.h>
#include <ogre_tools/movable_text.h>
#include <srs_ui_but/GetClosestPoint.h>
#include <srs_ui_but/ClosestPoint.h>
#include <time.h>
#include <GL/gl.h>

#define DEFAULT_ROBOT_LINK "/sdh_palm_link"
#define GET_CLOSEST_POINT_SERVICE "but_services/get_closest_point"

using namespace std;

namespace rviz
{

/**
 * @brief This tool displays closest point from oa selected robot's link.
 * @author Tomas Lokaj
 */
class CButDistanceLinearVisualizer : public rviz::Display

{
public:
  /**
   * @brief Constructor
   */
  CButDistanceLinearVisualizer(const string & name, rviz::VisualizationManager * manager);

  /**
   * @brief Destructor
   */
  virtual ~CButDistanceLinearVisualizer();

  /**
   * @brief Overriden method from Display
   */
  virtual void targetFrameChanged()
  {
  }
  /**
   * @brief Overriden method from Display
   */
  virtual void fixedFrameChanged()
  {
  }

  /**
   *  @brief Create display properties
   */
  virtual void createProperties();

  /**
   *  @brief Update display
   */
  virtual void update(float wall_dt, float ros_dt);

protected:
  /**
   *  @brief Create geometry (includes scene node initialization)
   */
  bool createGeometry();

  /**
   *  @brief Destroy geometry
   */
  void destroyGeometry();

  /**
   * @brief Display is enabled
   */
  virtual void onEnable();

  /**
   * @brief is Display disabled
   */
  virtual void onDisable();

  /**
   * @brief Get distance property
   * @return distance
   */
  const string getDistance()
  {
    ostringstream text_d;
    text_d << fabs(distance_) << " m";
    return text_d.str();
  }

  /**
   * @brief Gets link property
   * @return robot's link
   */
  const string getLinkString()
  {
    return robot_link_;
  }

  /**
   * @brief Gets color property
   * @return color
   */
  Color getColor()
  {
    return color_;
  }

  /**
   * Gets aplha property
   * @return alpha
   */
  float getAlpha()
  {
    return alpha_;
  }

  /**
   * @brief Gets thickness property
   * @return thickness
   */
  float getThickness()
  {
    return thickness_;
  }

  /**
   * @brief Gets draw distance text
   * @return show_distance
   */
  bool getShowDistance()
  {
    return show_distance_;
  }

  /**
   * @brief Sets link property
   * @param link is new link
   */
  void setLinkString(string link)
  {
    if (isEnabled())
      m_sceneNode_->setVisible(true);
    robot_link_ = link;
    propertyChanged(m_property_link_);
  }

  /**
   * @brief Sets color property
   * @param color is new color
   */
  void setColor(Color color)
  {
    color_ = color;
    material_->getTechnique(0)->setAmbient(color_.r_, color_.g_, color_.b_);
    propertyChanged(m_property_color_);
  }

  /**
   * @brief Sets alpha property
   * @param aplha is new alpha
   */
  void setAlpha(float alpha)
  {
    alpha_ = alpha;
    material_->getTechnique(0)->setAmbient(color_.r_, color_.g_, color_.b_);
    propertyChanged(m_property_alpha_);
  }

  /**
   * @brief Sets thickness property
   * @param thickness is new thickness
   */
  void setThickness(float thickness)
  {
    if (thickness > 0.1)
      thickness_ = 0.1;
    else
      thickness_ = thickness;
    propertyChanged(m_property_thickness_);
  }

  /**
   * @brief Sets draw distance text
   * @param show is new show_distance value
   */
  void setShowDistance(bool show)
  {
    show_distance_ = show;
    propertyChanged(m_show_distance_property_);
  }

  // Link
  string robot_link_;

  // Link and surface distance
  float distance_;

  // Scene node
  Ogre::SceneNode * m_sceneNode_;

  // Geometry manual object
  Ogre::ManualObject * line_manual_object_;

  // Material
  Ogre::MaterialPtr material_;

  // Display properties
  StringPropertyWPtr m_property_distance_;
  TFFramePropertyWPtr m_property_link_;
  FloatPropertyWPtr m_property_alpha_, m_property_thickness_;
  ColorPropertyWPtr m_property_color_;
  BoolPropertyWPtr m_show_distance_property_;
  IntPropertyWPtr m_refresh_property_;

  // Line color
  Color color_;

  // Line aplha
  float alpha_;

  // Line thickness
  float thickness_;

  // Draw distance text
  bool show_distance_;

  // Client for get_closest_point service
  ros::ServiceClient closestPointClient_;

  // GetClosestPoint Service parameters
  srs_ui_but::GetClosestPoint closestPointSrv_;

  // Closest point data
  srs_ui_but::ClosestPoint pointData_;

};
}
#endif /* BUT_DISTANCE_LINEAR_VISUALIZER_H_ */
