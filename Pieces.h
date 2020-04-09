#ifndef PIECES_H
#define PIECES_H

class Piece {
public:
    virtual ~Piece() = default;
    unsigned char color() const;
    unsigned char type() const;
    virtual bool canJump() const;
    virtual bool motionValidator(const int cx, const int cy, const int dx, const int dy) = 0;

protected:
    unsigned char m_color = 0;
    unsigned char m_type = 0;
};

class King : public Piece {
public:
    King(const unsigned char color);
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

class Queen : public Piece {
public:
    Queen(const unsigned char color);
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

class Bishop : public Piece {
public:
    Bishop(const unsigned char color);
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

class Knight : public Piece {
public:
    Knight(const unsigned char color);
    bool canJump() const override;
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

class Rook : public Piece {
public:
    Rook(const unsigned char color);
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

class Pawn : public Piece {
public:
    Pawn(const unsigned char color);
    bool motionValidator(const int cx, const int cy, const int dx, const int dy) override;
};

#endif // PIECES_H
