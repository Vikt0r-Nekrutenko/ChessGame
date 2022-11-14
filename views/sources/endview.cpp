#include "endview.hpp"
#include "gamemodel.hpp"
#include "menuview.hpp"

EndView::EndView(GameModel* model)
  : IView(model)
{
    model->results.save();
}

void EndView::show(Renderer& renderer)
{
    m_end.show(renderer, true);
    renderer.drawText(renderer.Size / 2 - m_end.Size() / 2 + m_end.markers().at(0),
                      static_cast<GameModel*>(m_model)->opponentName().c_str());
}

IView* EndView::keyEventsHandler(const int)
{
  static_cast<GameModel*>(m_model)->reset();
  return new MenuView(static_cast<GameModel*>(m_model));
}
