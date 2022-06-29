#include "tsapi.h"
#include "ts.h"

static ts_stream_t *ts = NULL;

int mpegts_init(int (* packet_output)( uint8_t *buf, uint32_t len ))
{
#if 0
    ts_param_t ts_param =
    {
        .audio_stream_id = 0xc0,
        .video_stream_id = 0xe0,
        .audio_pid = 0x101,
        .video_pid = 0x100,
        .pmt_pid = 0x1000,
        .pcr = 10,
        .output = packet_output,
        .program_count = 1,
        .program_list =
        {
            { 0x01, 0x1000 },
        }
    };
#endif    
    ts_param_t ts_param;
    ts_param.audio_stream_id = 0xc0;
    ts_param.video_stream_id = 0xe0;
    ts_param.audio_pid = 0x101;
    ts_param.video_pid = 0x100;
    ts_param.pmt_pid = 0x1000;
    ts_param.pcr = 10;
    ts_param.output = packet_output;
    ts_param.program_count = 1;
    ts_param.program_list[0].program_num = 0x01;
    ts_param.program_list[0].program_map_pid = 0x1000;

    ts = new_ts_stream( &ts_param );
    ts_write_pat( ts );
    ts_write_pmt( ts );
    return 0;
    
}

int mpegts_write_vframe(uint8_t *frame, int len, int iskey, int64_t timestamp)
{
    frame_info_t frame_info;

    frame_info.frame = frame;
    frame_info.timestamp = timestamp;
    frame_info.len = len;
    frame_info.frame_type = FRAME_TYPE_VIDEO;
    ts_write_frame( ts, &frame_info );
}

int mpegts_write_aframe(uint8_t *frame, int len, int64_t timestamp)
{
    frame_info_t frame_info;

    frame_info.frame = frame;
    frame_info.timestamp = timestamp;
    frame_info.len = len;
    frame_info.frame_type = FRAME_TYPE_AUDIO;
    ts_write_frame( ts, &frame_info );
    return -1;
}
