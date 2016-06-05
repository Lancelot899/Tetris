#include <array>
#include <time.h>

#include <QDebug>

#include "Tetris.h"


Block::Block() {
    memset(_position, 0, sizeof(int) * 2);
}

void Block::setPos(int x, int y) {
    _position[0] = x;
    _position[1] = y;
}

bool Block::getBlock(int *block) {
    if(block == nullptr)
        return false;

    for(int i = 0; i <= 3; ++i) {
        block[2 * i] = _points[i * 2] + _position[0];
        block[2 * i + 1] = _points[i * 2 + 1] + _position[1];
    }
    return true;
}


void _rotate_(int *points, int* ans) {
    for(int i = 0; i <= 3; ++i) {
        ans[i * 2] = -points[i * 2 + 1];  // x = -y
        ans[i * 2 + 1] = points[i * 2];   // y = x
    }
}

void _transpose_(int *pos, int *ans, Block::Transpositaion trans) {
    switch (trans) {
    case Block::Left:
        ans[1] = pos[1];
        ans[0] = pos[0] - 1;
        break;
    case Block::Right:
        ans[0] = pos[0] + 1;
        ans[1] = pos[1];
        break;
    case Block::Down:
        ans[0] = pos[0];
        ans[1] = pos[1] + 1;
        break;
    default:
        break;
    }
}

bool rotate(int *position, int *points, std::shared_ptr<GameMap>& map) {
    int ans[8];
    memset(ans, 0, sizeof(int) * 8);
    _rotate_(points, ans);
    for(int i = 0; i <= 3; ++i) {
        if(ans[i * 2] + position[0] < 0 || ans[i * 2] + position[0] >= Tetris::MapWidth ||
                ans[i * 2 + 1] + position[1] >= Tetris::MapHeight)
            return false;

        if(map->at(position[0] + ans[i * 2], position[1] + ans[i * 2 + 1]))
            return false;
    }
    memcpy(points, ans, sizeof(int) * 8);
    return true;
}

bool transpose(int *position, int *points, Block::Transpositaion trans, std::shared_ptr<GameMap>& map) {
    int ans[2]; memset(ans, 0, sizeof(int) * 2);
    _transpose_(position, ans, trans);

    for(int i = 0; i <= 3; ++i) {
        if(ans[0] + points[2 * i] < 0 || ans[0] + points[2 * i] >= Tetris::MapWidth
                || ans[1] + points[2 * i + 1] >= Tetris::MapHeight)
            return false;

        if(map->at(ans[0] + points[i * 2], ans[1] + points[i * 2 + 1]))
            return false;
    }
    memcpy(position, ans, 2 * sizeof(int));
    return true;
}

class OBlock : public Block {
public:
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    OBlock ();
    ~OBlock() {}
};

bool OBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap>& map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType OBlock::getShape(){
    return Shape_O;
}

OBlock::OBlock() {
    _points[0] = 0;
    _points[1] = 0;
    _points[2] = 1;
    _points[3] = 0;
    _points[4] = 0;
    _points[5] = 1;
    _points[6] = 1;
    _points[7] = 1;
}


class TBlock : public Block {
public:
    bool rotate(std::shared_ptr<GameMap>& map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    TBlock();
    ~TBlock() {}
};

bool TBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}

bool TBlock::transpose(Block::Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType TBlock::getShape() {
    return Shape_T;
}

TBlock::TBlock() {
    _points[0] = -1;
    _points[1] = 0;
    _points[2] = 0;
    _points[3] = 0;
    _points[4] = 1;
    _points[5] = 0;
    _points[6] = 0;
    _points[7] = 1;
}


class SBlock : public Block {
public:
    bool rotate(std::shared_ptr<GameMap> &map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    SBlock();
    ~SBlock() {}
};

bool SBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}

bool SBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType SBlock::getShape() {
    return Shape_S;
}

SBlock::SBlock() {
    _points[0] = 0;
    _points[1] = 0;
    _points[2] = 1;
    _points[3] = 0;
    _points[4] = -1;
    _points[5] = 1;
    _points[6] = 0;
    _points[7] = 1;
}


class ZBlock : public Block {
public:
    bool rotate(std::shared_ptr<GameMap> &map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    ZBlock();
    ~ZBlock() {}
};

bool ZBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}

bool ZBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType ZBlock::getShape() {
    return Shape_Z;
}

ZBlock::ZBlock() {
    _points[0] = -1;
    _points[1] = 0;
    _points[2] = 0;
    _points[3] = 0;
    _points[4] = 0;
    _points[5] = 1;
    _points[6] = 1;
    _points[7] = 1;
}

class IBlock : public Block {
public:
    bool rotate(std::shared_ptr<GameMap> &map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    IBlock();
    ~IBlock() {}
};

bool IBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}

bool IBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType IBlock::getShape() {
    return Shape_I;
}

IBlock::IBlock() {
    _points[0] = -1;
    _points[1] = 0;
    _points[2] = 0;
    _points[3] = 0;
    _points[4] = 1;
    _points[5] = 0;
    _points[6] = 2;
    _points[7] = 0;
}

class LBlock : public Block {
public :
    bool rotate(std::shared_ptr<GameMap> &map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    LBlock();
    ~LBlock() {}
};

bool LBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType LBlock::getShape() {
    return Shape_L;
}

LBlock::LBlock() {
    _points[0] = 0;
    _points[1] = 0;
    _points[2] = 1;
    _points[3] = 0;
    _points[4] = 2;
    _points[5] = 0;
    _points[6] = 0;
    _points[7] = 1;
}

bool LBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}

class JBlock : public Block {
public :
    bool rotate(std::shared_ptr<GameMap> &map);
    bool transpose(Transpositaion trans, std::shared_ptr<GameMap> &map);
    BlockType getShape();

    JBlock();
    ~JBlock() {}
};

bool JBlock::transpose(Transpositaion trans, std::shared_ptr<GameMap> &map) {
    return ::transpose(this->_position, this->_points, trans, map);
}

BlockType JBlock::getShape() {
    return Shape_J;
}

JBlock::JBlock() {
    _points[0] = -2;
    _points[1] = 0;
    _points[2] = -1;
    _points[3] = 0;
    _points[4] = 0;
    _points[5] = 0;
    _points[6] = 0;
    _points[7] = 1;
}

bool JBlock::rotate(std::shared_ptr<GameMap> &map) {
    return ::rotate(this->_position, this->_points, map);
}



Tetris::Tetris()
    : _map(new GameMap(MapWidth, MapHeight)),
      _isrunning(false), _curPoint(0),
      _maxPoint(0), _playTimes(0) {
    _blocks.push_back(pBlock(new OBlock));
    _blocks.push_back(pBlock(new TBlock));
    _blocks.push_back(pBlock(new JBlock));
    _blocks.push_back(pBlock(new ZBlock));
    _blocks.push_back(pBlock(new IBlock));
    _blocks.push_back(pBlock(new SBlock));
    _blocks.push_back(pBlock(new LBlock));
    // _map->at(0, 0) = 1;
    time_t tm;
    time(&tm);
    srand(tm);
    int type = rand() % 7;
    choseBlock((BlockType)type);
    _curBlock = _nextBlock;
    type = rand() % 7;
    choseBlock((BlockType)type);
    //_nextBlock = _blocks[2];
//    for(int i = 1; i < MapWidth; ++i) {
//        _map->at(i, MapHeight - 1) = 1;
//    }
}

void Tetris::run() {
    _isrunning = true;
}

void Tetris::pause() {
    _isrunning = false;
}

void Tetris::reset() {
    _curPoint = 0;
    _curBlock->setPos(MapWidth / 2, 0);
    _map->clear();
}

bool Tetris::action(Tetris::Action act) {
    if(_isrunning == false)
        return false;
    bool res = false;
    switch (act) {
    case Rotate:
        //qDebug() << "rotate";
        res = _curBlock->rotate(_map);
        break;
    case Down:
        res = _curBlock->transpose(Block::Transpositaion::Down, _map);
        if(!res) {
            clearRow();
            newBlock();
        }
        break;
    case Left:
        res = _curBlock->transpose(Block::Transpositaion::Left, _map);
        break;
    case Right:
        res = _curBlock->transpose(Block::Transpositaion::Right, _map);
        break;
    default:
        break;
    }
    return res;
}

bool Tetris::choseBlock(BlockType type) {
    if(type < 0 || type > 7)
        return false;
    _nextBlock = _blocks[int(type)];
    _nextBlock->setPos(MapWidth / 2, 0);
    return true;
}

bool Tetris::clearRow() {
    int rows[4];
    memset(rows, 0, sizeof(int) * 4);
    int clrowNum(0);
    int pos[8];
    memset(pos, 0, sizeof(int) * 8);
    _curBlock->getBlock(pos);

    for(int i = 0; i <= 3; ++i) {
        int ix = pos[2*i + 0];
        int iy = pos[2*i + 1];
        int &v = _map->at(ix, iy);
        v = 1;
    }

//    printf("1: %d-%d\n2: %d-%d\n3: %d-%d\n4: %d-%d\n", pos[0], pos[1], pos[2], pos[3],
//            pos[4], pos[5], pos[6], pos[7]);
    for(int j = 0; j <= 3; ++j) {
        //bool isClean = false;
        int i = 0;
        for (; i < _map->getMapWidth(); ++i) {
            //printf("map[%d, %d] = %d\n", i, pos[2 * j + 1], _map->at(i, pos[2 * j + 1]));
            if(!_map->at(i, pos[2 * j + 1])) {
                break;
            }
        }
        if(i == _map->getMapWidth()) {
            rows[clrowNum++] = pos[2 * j + 1];
        }
    }

 //   qDebug() << clrowNum;

    // clean
    if(clrowNum) {
        for(int i = 1; i <= clrowNum; ++i) {
            _curPoint += i * 10;
        }
        // sort
        for (int i = 0; i < clrowNum; i++) {
            for (int j = i; j < clrowNum; j++) {
                if (rows[i] > rows[j]) {
                    int temp = rows[i];
                    rows[i] = rows[j];
                    rows[j] = temp;
                }
            }
        }

        //copy
//        printf("copy");
        for(int j = 0; j < clrowNum; ++j) {
            for(int row = rows[j]; row > 0; --row) {
                memcpy(&_map->at(0, row), &_map->at(0, row - 1), sizeof(int) * _map->getMapWidth());
            }
        }
        return true;
    }
    return false;
}

void Tetris::newBlock() {
    //qDebug() << "Tetris::newBlock";

    _curBlock = _nextBlock;
    BlockType type = BlockType(rand() % 7);
    choseBlock(type);
}

bool Tetris::isOver() {
    for(int i = 0; i < MapWidth; ++i)
        if(_map->at(i, 0)) {
            if(_curPoint > _maxPoint)
                _maxPoint = _curPoint;
            ++_playTimes;
            return true;
        }
    return false;
}

void GameMap::clear() {
    memset(_data, 0, sizeof(int) * _width * _height);
}
