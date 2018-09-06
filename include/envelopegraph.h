#pragma once

#include "wx/wx.h"
#include <vector>

#define SCROLL_RATE 10

using std::vector;

/** Implements a graphical component that provides dragable nodes joining straight lines */
class EnvelopeGraph: public wxScrolledWindow
{
    public:
        /** @brief  Construct an envelope graph object
            @param  parent Pointer to the parent window
        */
        EnvelopeGraph(wxWindow* parent);

        /** @brief  Destruct envelope graph object */
        ~EnvelopeGraph();

        /** @brief  Add a node to the graph
            @param  node wxPoint representing position of node relative to top left of control
            @param  refresh Set true to refresh display after adding node (Default: true)
            @retval bool True on success
            @note   Cannot exceed maximum nodes
            @note   Node is inserted at horizontal position
        */
        bool AddNode(wxPoint node, bool refresh = true);

        /** @brief  Remove a node from the graph
        *   @param  index Index of the node to remove
        *   @param  refresh Set true to refresh display after removing node (Default: true)
        *   @retval bool True on success
        *   @note   Cannot remove last two nodes
        */
        bool RemoveNode(unsigned int index, bool refresh = true);

        /** @brief  Clear all nodes from graph
        *   @param  refresh Set true to refresh display after clearing nodes (Default: true)
        */
        void Clear(bool refresh = true);

    private:
        void DrawGraph(wxDC& dc); //Draws the lines and nodes
        void OnPaint(wxPaintEvent &event); //Handle paint event
        void OnMouseLeftDown(wxMouseEvent &event); //Handle left mouse button press
        void OnMouseLeftUp(wxMouseEvent &event); //Handle left mouse button release
        void OnMotion(wxMouseEvent &event); //Handle mouse movement
        void OnMouseLeftDClick(wxMouseEvent &event); //Handle left mouse button double click
        void OnEnterWindow(wxMouseEvent &event); //Handle mouse entering window
        void OnSize(wxSizeEvent &event); //Handle window resizing
        void OnRightDown(wxMouseEvent &event); //Handle right mosue button press
        void OnRightUp(wxMouseEvent &event); //Handle right mosue button release
        void OnRightDClick(wxMouseEvent &event); //Handle right mouse button double click
        bool IsPointInRegion(wxPoint point, wxPoint centre, unsigned int radius); //True if point is within radius of centre (actually square)
        wxPoint GetNodeCentre(wxPoint ptNode); //Get the location of a node in the display
        wxPoint GetNodeFromCentre(wxPoint ptPos); //Get the node value from its location in the display
        unsigned int m_nMaxNodes; //Maximum quantity of nodes
        unsigned int m_nNodeRadius; //Radius of node
        int m_nScaleX; //Scale factor of display to X data value
        int m_nScaleY; //Scale factor of display to Y data value
        int m_nPxScrollH; //Quantity of pixesl per scroll unit horizontal
        int m_nPxScrollV; //Quantity of pixesl per scroll unit vertical
        int m_nDragNode; //Index of node being dragged. -1 for none

        int m_nMinimumY; //Minimum Y value for a node
        int m_nMaximumY; //Maximum Y value for a node
        wxPoint m_ptOrigin; //Position of first node

        wxWindow* m_pParent; //Parent window
        wxRegion* m_pRegionDrag; //Region for permissible drag (window minus diameter of nodes
        wxColour m_colourLine; //Colour of graph lines
        wxColour m_colourNode; //Colour of graph nodes
        wxPoint m_pointClickOffset; //Offset of left click from center of selected node
        vector<wxPoint> m_vNodes; //Table of nodes

        wxStaticText* m_pLabel;
        DECLARE_EVENT_TABLE();
};

