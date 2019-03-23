#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

#include <QWidget>
#include <QMouseEvent>

/*!
 * \brief The Scratchpad class is a widget responsible for providing means
 *        for the user to draw a curve (path) on a scratchpad
 *
 * The class handles the mouse events that occur when user attempts to draw
 * a path on the scratchpad. Path can be drawn by left click and move of the mouse
 * while the left button still pressed. Only one path at a time can be drawn on
 * the scratchpad.
 */
class Scratchpad : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Scratchpad constructs a new Scratchpad
     * \param[in] parent a parent widget
     *
     * This class must have a parent as size of the scratchpad depends on it.
     */
    explicit Scratchpad(QWidget *parent);

    /*!
     * \brief ~Scratchpad destructs the Scratchpad
     */
    ~Scratchpad() override {}

    /*!
     * \brief setPenColor sets a color of a drawing device
     * \param[in] color
     */
    void setPenColor(QColor color) {color_ = color;}

    /*!
     * \brief setPenWidth sets width of a drawing device
     * \param[in] width
     */
    void setPenWidth(int width) {thickness_ = width;}

    /*!
     * \return current color of a drawing device
     */
    QColor getPenColor() const {return color_;}

    /*!
     * \return current width of a drawing device
     */
    int getPenWidth() const {return thickness_;}

    /*!
     * \brief isDrawingValid checks whether any curve has been drawn
     * \return true when any curve has been drawn, otherwise false
     */
    bool isDrawingValid() const;

    /*!
     * \brief clearScratchpad clears the scrathpad so a new curve can be drawn on it
     */
    void clearScratchpad();

    /*!
     * \brief generatePathData generates a file that contains information
     *        about points that form the path being drawn
     * \param[in] filePath a path to the to be generated file
     * \return true on success, false otherwise
     *
     * Assumes that validity of the path has been checked.
     */
    virtual bool generatePathData(const QString filePath) const;

signals:
    /*!
     * \brief mouseCorrectReleaseEvent is emitted when user finishes drawing a path
     */
    void mouseCorrectReleaseEvent();

private slots:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Scratchpad() = delete;
    void addPointToPathData(QPoint point);

    std::list<QPoint> pathData_;
    QImage            image_;
    QColor            color_;
    int               thickness_;
    QPoint            lastPosition_;
    bool              alreadyDrawn_;
};

#endif // SCRATCHPAD_H
