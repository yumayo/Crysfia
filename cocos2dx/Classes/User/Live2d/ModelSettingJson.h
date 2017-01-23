/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "ModelSetting.h"
#include "util/Json.h"

// JSONのキー
const char NAME [ ] = "name";
const char MODEL [ ] = "model";
const char _ID [ ] = "id";
const char TEXTURES [ ] = "textures";
const char TEXTURE_DIR [ ] = "texture_dir";
const char INIT_PARAM [ ] = "init_param";
const char INIT_PARTS_VISIBLE [ ] = "init_parts_visible";
const char HIT_AREAS [ ] = "hit_areas";
const char EXPRESSIONS [ ] = "expressions";
const char POSE [ ] = "pose";
const char PHYSICS [ ] = "physics";
const char MOTION_GROUPS [ ] = "motions";
const char SOUND [ ] = "sound";
const char FADE_IN [ ] = "fade_in";
const char FADE_OUT [ ] = "fade_out";
const char VAL [ ] = "val";
const char LAYOUT [ ] = "layout";
const char _FILE [ ] = "file";

class ModelSettingJson : public ModelSetting
{
private:
    live2d::Json* json;
    // キーが存在するかどうかのチェック
    bool existModelName( ) { return !json->getRoot( )[NAME].isNull( ); }
    bool existModelFile( ) { return !json->getRoot( )[MODEL].isNull( ); }
    bool existTextureFiles( ) { return !json->getRoot( )[TEXTURES].isNull( ); }
    bool existInitParam( ) { return !json->getRoot( )[INIT_PARAM].isNull( ); }
    bool existInitPartsVisible( ) { return !json->getRoot( )[INIT_PARTS_VISIBLE].isNull( ); }
    bool existHitAreas( ) { return !json->getRoot( )[HIT_AREAS].isNull( ); }
    bool existPhysicsFile( ) { return !json->getRoot( )[PHYSICS].isNull( ); }
    bool existPoseFile( ) { return !json->getRoot( )[POSE].isNull( ); }
    bool existExpressionFile( ) { return !json->getRoot( )[EXPRESSIONS].isNull( ); }
    bool existMotionGroups( ) { return !json->getRoot( )[MOTION_GROUPS].isNull( ); }
    bool existMotionGroup( std::string name ) { return !json->getRoot( )[MOTION_GROUPS][name.c_str( )].isNull( ); }
    bool existMotionSound( std::string name, int n ) { return !json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][SOUND].isNull( ); }
    bool existMotionFadeIn( std::string name, int n ) { return !json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][FADE_IN].isNull( ); }
    bool existMotionFadeOut( std::string name, int n ) { return !json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][FADE_OUT].isNull( ); }

public:
    ModelSettingJson( const char* buf, size_t size ) {
        json = live2d::Json::parseFromBytes( buf, (int)size );
    }
    ~ModelSettingJson( ) {
        delete json;
    }

    // モデルデータについて
    std::string getModelName( )
    {
        if ( !existModelName( ) )return "";
        return json->getRoot( )[NAME].toString( ).c_str( );
    }


    std::string getModelFile( )
    {
        if ( !existModelFile( ) )return "";
        return json->getRoot( )[MODEL].toString( ).c_str( );
    }

    // テクスチャについて
    int getTextureNum( )
    {
        if ( !existTextureFiles( ) )return 0;
        return json->getRoot( )[TEXTURES].size( );
    }

    virtual std::string getTextureDir( )
    {
        return json->getRoot( )[TEXTURE_DIR].c_str( );
    }

    std::string getTextureFile( int n ) { return json->getRoot( )[TEXTURES][n].toString( ).c_str( ); }

    // 初期パラメータについて
    int getInitParamNum( )
    {
        if ( !existInitParam( ) )return 0;
        return json->getRoot( )[INIT_PARAM].size( );
    }


    float getInitParamValue( int n ) { return json->getRoot( )[INIT_PARAM][n][VAL].toDouble( ); }
    std::string getInitParamID( int n ) { return json->getRoot( )[INIT_PARAM][n][_ID].toString( ).c_str( ); }

    // 初期パーツ表示について
    int getInitPartsVisibleNum( )
    {
        if ( !existInitPartsVisible( ) )return 0;
        return json->getRoot( )[INIT_PARTS_VISIBLE].size( );
    }


    float getInitPartsVisibleValue( int n ) { return json->getRoot( )[INIT_PARTS_VISIBLE][n][VAL].toDouble( ); }
    std::string getInitPartsVisibleID( int n ) { return json->getRoot( )[INIT_PARTS_VISIBLE][n][_ID].toString( ).c_str( ); }


    // あたり判定について
    int getHitAreasNum( )
    {
        if ( !existHitAreas( ) )return 0;
        return json->getRoot( )[HIT_AREAS].size( );
    }

    std::string getHitAreaID( int n ) { return json->getRoot( )[HIT_AREAS][n][_ID].toString( ).c_str( ); }
    std::string getHitAreaName( int n ) { return json->getRoot( )[HIT_AREAS][n][NAME].toString( ).c_str( ); }

    // 物理演算、パーツ切り替え、表情ファイルについて
    std::string getPhysicsFile( )
    {
        if ( !existPhysicsFile( ) )return "";
        return json->getRoot( )[PHYSICS].toString( ).c_str( );
    }


    std::string getPoseFile( )
    {
        if ( !existPoseFile( ) )return "";
        return json->getRoot( )[POSE].toString( ).c_str( );
    }


    int getExpressionNum( )
    {
        if ( !existExpressionFile( ) )return 0;
        return json->getRoot( )[EXPRESSIONS].size( );
    }


    std::string getExpressionFile( int n )
    {
        return json->getRoot( )[EXPRESSIONS][n][_FILE].toString( ).c_str( );
    }


    std::string getExpressionName( int n )
    {
        return json->getRoot( )[EXPRESSIONS][n][NAME].toString( ).c_str( );
    }


    // モーションについて
    int getMotionNum( std::string name )
    {
        if ( !existMotionGroup( name ) )return 0;
        return json->getRoot( )[MOTION_GROUPS][name.c_str( )].size( );
    }


    std::string getMotionFile( std::string name, int n )
    {
        if ( !existMotionGroup( name ) )return "";
        return json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][_FILE].toString( ).c_str( );
    }


    std::string getMotionSound( std::string name, int n )
    {
        if ( !existMotionSound( name, n ) )return "";
        return json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][SOUND].toString( ).c_str( );
    }


    int getMotionFadeIn( std::string name, int n )
    {
        if ( !existMotionFadeIn( name, n ) )return 1000;
        return json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][FADE_IN].toInt( );
    }


    int getMotionFadeOut( std::string name, int n )
    {
        if ( !existMotionFadeOut( name, n ) )return 1000;
        return json->getRoot( )[MOTION_GROUPS][name.c_str( )][n][FADE_OUT].toInt( );
    }


    int getMotionGroupNum( )
    {
        if ( !existMotionGroups( ) ) {
            return 0;
        }
        return json->getRoot( )[MOTION_GROUPS].getKeys( ).size( );
    }


    std::string getMotionGroupName( int n )
    {
        if ( !existMotionGroups( ) ) {
            return NULL;
        }
        return json->getRoot( )[MOTION_GROUPS].getKeys( )[n].c_str( );
    }


    bool getLayout( std::map<std::string, float> & layout )
    {
        live2d::LDMap<live2d::LDString, live2d::Value* > * map = json->getRoot( )[LAYOUT].getMap( );
        if ( map == NULL ) {
            return false;
        }
        live2d::LDMap<live2d::LDString, live2d::Value* >::const_iterator map_ite;
        bool ret = false;
        for ( map_ite = map->begin( ); map_ite != map->end( ); map_ite++ )
        {
            layout[( *map_ite ).first.c_str( )] = ( *map_ite ).second->toDouble( );
            ret = true;
        }
        return ret;
    }

};