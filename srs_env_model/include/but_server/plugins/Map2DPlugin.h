/******************************************************************************
 * \file
 *
 * $Id:$
 *
 * Copyright (C) Brno University of Technology
 *
 * This file is part of software developed by dcgm-robotics@FIT group.
 *
 * Author: Vit Stancl (stancl@fit.vutbr.cz)
 * Supervised by: Michal Spanel (spanel@fit.vutbr.cz)
 * Date: dd/mm/2012
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

#ifndef Map2DPlugin_H_included
#define Map2DPlugin_H_included

#include <but_server/ServerTools.h>
#include <nav_msgs/OccupancyGrid.h>
#include <message_filters/subscriber.h>
#include <tf/message_filter.h>

namespace srs
{

    class CMap2DPlugin : public CServerPluginBase, public COctomapCrawlerBase<tButServerOcTree::NodeType>, public CDataHolderBase< nav_msgs::OccupancyGrid >
    {
    public:
        /// Constructor
        CMap2DPlugin(const std::string & name);

        /// Destructor
        virtual ~CMap2DPlugin();

        //! Enable or disable publishing
        void enable( bool enabled ){ m_publishMap2D = enabled; }

        //! Should plugin publish data?
        bool shouldPublish();

        //! Initialize plugin - called in server constructor
        virtual void init(ros::NodeHandle & node_handle);

        //! Called when new scan was inserted and now all can be published
        virtual void onPublish(const ros::Time & timestamp);

        //! Set used octomap frame id and timestamp
        virtual void onFrameStart( const SMapParameters & par );

        //! Handle free node (does nothing here)
        virtual void handleFreeNode(tButServerOcTree::iterator & it, const SMapParameters & mp );

        /// hook that is called when traversing occupied nodes of the updated Octree (does nothing here)
        virtual void handleOccupiedNode(srs::tButServerOcTree::iterator& it, const SMapParameters & mp);

        /// Called when all nodes was visited.
        virtual void handlePostNodeTraversal(const SMapParameters & mp);

    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    protected:
        //! Is publishing enabled?
        bool m_publishMap2D;

        //! Collision object publisher name
        std::string m_map2DPublisherName;

        /// Collision object publisher
        ros::Publisher m_map2DPublisher;

        //! Transform listener
        tf::TransformListener m_tfListener;

        //
        bool m_latchedTopics;

        //! Used frame id (input data will be transformed to it)
        std::string m_map2DFrameId;

        /// Crawled octomap frame id
        std::string m_ocFrameId;

        /// Transformation from octomap to the collision object frame id - rotation
        Eigen::Matrix3f m_ocToMap2DRot;

        /// Transformation from octomap to the collision object frame id - translation
        Eigen::Vector3f m_ocToMap2DTrans;

        /// Padded key minimum
        octomap::OcTreeKey m_paddedMinKey;

        /// Map limits
        double m_minSizeX;
        double m_minSizeY;

        /// Conversion between frame id's must be done...
        bool m_bConvert;

    }; // class CMap2DPlugin

    /// Declare holder object - partial specialization of the default holder with predefined connection settings
    template< class tpOctomapPlugin >
    struct SMap2DPluginHolder : public  srs::CCrawlingPluginHolder< srs::CMap2DPlugin, tpOctomapPlugin >
    {
    protected:
        /// Define holder type
        typedef srs::CCrawlingPluginHolder< srs::CMap2DPlugin, tpOctomapPlugin > tHolder;

    public:
        /// Create holder
        SMap2DPluginHolder( const std::string & name )
        : tHolder(  name,  tHolder::ON_START | tHolder::ON_OCCUPIED | tHolder::ON_FREE | tHolder::ON_STOP)
        {

        }

    }; // struct SMap2DPluginHolder

} // namespace srs



// namespace srs


// Map2DPlugin_H_included
#endif

