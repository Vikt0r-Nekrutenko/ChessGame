#ifndef PIECES_H
#define PIECES_H

class Piece {
public:
    virtual ~Piece() = default;
    void move();
    unsigned moves() const;
    unsigned char color() const;
    unsigned char type() const;
    virtual bool canJump() const;
    virtual bool motionIsValid(const int cx, const int cy, const int dx, const int dy, const Piece *opponent) = 0;

protected:
    unsigned char m_color = 0;
    unsigned char m_type = 0;
    unsigned m_moves = 0;
};

#endif // PIECES_H
