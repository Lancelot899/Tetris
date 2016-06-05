#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
#include <memory>

enum BlockType {
    Shape_O     = 0,
    Shape_T     = 1,
    Shape_J     = 2,
    Shape_Z     = 3,
    Shape_I     = 4,
    Shape_S     = 5,
    Shape_L     = 6,
    Shape_None  = 7
};

class GameMap;

class Block {
public:
    enum Transpositaion {
        None  = 0,
        Left  = 1,
        Right = 2,
        Down  = 3
    };

public:
    Block();
    virtual ~Block() {}

public:
    virtual bool rotate(std::shared_ptr<GameMap>& ) { return true;}
    virtual bool transpose(Transpositaion, std::shared_ptr<GameMap>& ) { return true; }

    virtual BlockType getShape() { return Shape_None; }
    void setPos(int x, int y);

    bool getBlock(int *block);

protected:
    int                    _points[8];
    int                    _position[2];
};

class GameMap {
public:
    GameMap(int width, int height) : _width(width), _height(height) {
        _data = (int*)malloc(_width * _height * sizeof(int));
        memset(_data, 0, sizeof(int) *_width * _height);
    }

    ~GameMap() {free(_data);}

public:
    const int* getData() {return _data;}

    ///
    /// \brief at
    ///
    /// \param i - horiztonal direct
    /// \param j - vertical direction
    ///
    /// \return
    ///
    int& at(int i, int j) {return _data[i + j * _width];}
    int getMapWidth() { return _width;}
    int getMapHeight() { return _height;}
    void clear();

    //void setBlocks(int *block, BlockType type);

private:
    GameMap() {}

private:
    int *_data;
    int _width;
    int _height;
};

typedef std::shared_ptr<Block> pBlock;

class Tetris {
public:
    enum {
        MapWidth = 20,
        MapHeight = 40
    };

    enum Action {
        Rotate = 'W',
        Left   = 'A',
        Right  = 'D',
        Down   = 'S'
    };

public:
    Tetris();
    std::shared_ptr<GameMap> getMap() { return _map; }

    pBlock getCurBlock() {return _curBlock;}
    BlockType getNextBlockType() { return _nextBlock->getShape();}

public:
    bool isRunning() { return _isrunning; }
    void run();
    void pause();
    void reset();
    bool action(Action act);
    bool isOver();
    int  getCurPoint() { return _curPoint; }
    int  getMaxPoint() { return _maxPoint; }
    int  getPlayTimes() { return _playTimes; }

private:
    bool choseBlock(BlockType type);
    bool clearRow();
    void newBlock();


private:
    std::vector<pBlock>          _blocks;
    pBlock                       _curBlock;
    pBlock                       _nextBlock;
    std::shared_ptr<GameMap>     _map;
    bool                         _isrunning;

private:
    int                         _curPoint;
    int                         _maxPoint;
    int                         _playTimes;
};

#endif // TETRIS_H
