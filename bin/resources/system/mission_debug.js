function CreateDebugMenu()
{
  var topmenu = new ContextMenu("TopMenu");
  topmenu.addItem("","Debug");
  topmenu.addItemWithCallback("Debug/enemies", "add_enemy_archers", function() {engine.log("test");} );

 /*
    ADD_DEBUG_EVENT( enemies, add_enemy_soldiers )
    ADD_DEBUG_EVENT( enemies, add_chastener_soldiers )
    ADD_DEBUG_EVENT( enemies, add_wolves )
    ADD_DEBUG_EVENT( enemies, send_chastener )
    ADD_DEBUG_EVENT( enemies, add_empire_barbarian )
    ADD_DEBUG_EVENT( enemies, send_barbarian_to_player )
    ADD_DEBUG_EVENT( enemies, kill_all_enemies )

    ADD_DEBUG_EVENT( requests, comply_rome_request )
    ADD_DEBUG_EVENT( requests, test_request )

    ADD_DEBUG_EVENT( divinity, send_mars_wrath )
    ADD_DEBUG_EVENT( divinity, send_mars_spirit )
    ADD_DEBUG_EVENT( divinity, send_venus_wrath )
    ADD_DEBUG_EVENT( divinity, send_neptune_wrath )
    ADD_DEBUG_EVENT( divinity, send_venus_smallcurse )

    ADD_DEBUG_EVENT( money, add_1000_dn )
    ADD_DEBUG_EVENT( money, add_player_money )

    ADD_DEBUG_EVENT( goods, add_wheat_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_fish_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_meat_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_olives_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_fruit_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_grape_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_vegetable_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_clay_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_timber_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_iron_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_marble_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_pottery_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_furniture_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_weapons_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_wine_to_warehouse )
    ADD_DEBUG_EVENT( goods, add_oil_to_warehouse )

    ADD_DEBUG_EVENT( goods, add_wheat_to_granary )
    ADD_DEBUG_EVENT( goods, add_fish_to_granary )
    ADD_DEBUG_EVENT( goods, add_meat_to_granary )
    ADD_DEBUG_EVENT( goods, add_fruit_to_granary )
    ADD_DEBUG_EVENT( goods, add_vegetable_to_granary )

    ADD_DEBUG_EVENT( factories, all_wheatfarms_ready )
    ADD_DEBUG_EVENT( factories, all_wahrf_ready )
    ADD_DEBUG_EVENT( factories, all_olivefarms_ready )
    ADD_DEBUG_EVENT( factories, all_fruitfarms_ready )
    ADD_DEBUG_EVENT( factories, all_grapefarms_ready )
    ADD_DEBUG_EVENT( factories, all_vegetablefarms_ready )
    ADD_DEBUG_EVENT( factories, all_claypit_ready )
    ADD_DEBUG_EVENT( factories, all_timberyard_ready )
    ADD_DEBUG_EVENT( factories, all_ironmine_ready )
    ADD_DEBUG_EVENT( factories, all_marblequarry_ready )
    ADD_DEBUG_EVENT( factories, all_potteryworkshtp_ready )
    ADD_DEBUG_EVENT( factories, all_furnitureworksop_fillstock )
    ADD_DEBUG_EVENT( factories, all_furnitureworksop_ready )
    ADD_DEBUG_EVENT( factories, all_weaponworkshop_ready )
    ADD_DEBUG_EVENT( factories, all_wineworkshop_ready )
    ADD_DEBUG_EVENT( factories, all_oilworkshop_ready )
    ADD_DEBUG_EVENT( factories, all_creamery_fillstock )

    ADD_DEBUG_EVENT( other, send_player_army )
    ADD_DEBUG_EVENT( other, screenshot )
    ADD_DEBUG_EVENT( other, enable_constructor_mode )
    ADD_DEBUG_EVENT( other, next_theme )

    ADD_DEBUG_EVENT( buildings, toggle_shipyard_enable )
    ADD_DEBUG_EVENT( buildings, toggle_reservoir_enable )
    ADD_DEBUG_EVENT( buildings, toggle_wineshop_enable )
    ADD_DEBUG_EVENT( buildings, toggle_vinard_enable )

    ADD_DEBUG_EVENT( disaster, random_fire )
    ADD_DEBUG_EVENT( disaster, random_collapse )
    ADD_DEBUG_EVENT( disaster, random_plague )
    ADD_DEBUG_EVENT( disaster, earthquake )
    ADD_DEBUG_EVENT( disaster, fill_random_claypit )
    ADD_DEBUG_EVENT( disaster, forest_fire )

    ADD_DEBUG_EVENT( level, win_mission )
    ADD_DEBUG_EVENT( level, fail_mission )
    ADD_DEBUG_EVENT( level, change_emperor )
    ADD_DEBUG_EVENT( level, property_browser )
    ADD_DEBUG_EVENT( level, show_requests )
    ADD_DEBUG_EVENT( level, show_attacks )

    ADD_DEBUG_EVENT( empire, send_merchants )
    ADD_DEBUG_EVENT( empire, toggle_lock_empiremap )
    ADD_DEBUG_EVENT( empire, empire_toggle_capua )
    ADD_DEBUG_EVENT( empire, empire_toggle_londinium )

    ADD_DEBUG_EVENT( in_city, add_soldiers_in_fort )
    ADD_DEBUG_EVENT( in_city, add_city_border )
    ADD_DEBUG_EVENT( in_city, crash_favor )
    ADD_DEBUG_EVENT( in_city, add_scribe_messages )
    ADD_DEBUG_EVENT( in_city, show_fest )
    ADD_DEBUG_EVENT( in_city, add_favor )
    ADD_DEBUG_EVENT( in_city, remove_favor )
    ADD_DEBUG_EVENT( in_city, make_generation )
    ADD_DEBUG_EVENT( in_city, decrease_sentiment )
    ADD_DEBUG_EVENT( in_city, increase_sentiment )
    ADD_DEBUG_EVENT( in_city, forest_grow )
    ADD_DEBUG_EVENT( in_city, reset_fire_risk )
    ADD_DEBUG_EVENT( in_city, reset_collapse_risk )

    ADD_DEBUG_EVENT( house, increase_max_level )
    ADD_DEBUG_EVENT( house, decrease_max_level )
    ADD_DEBUG_EVENT( house, increase_house_level )
    ADD_DEBUG_EVENT( house, decrease_house_level )
    ADD_DEBUG_EVENT( house, lock_house_level )

    ADD_DEBUG_EVENT( options, run_script )
    ADD_DEBUG_EVENT( options, all_sound_off )
    ADD_DEBUG_EVENT( options, reload_aqueducts )
    ADD_DEBUG_EVENT( options, toggle_experimental_options )
    ADD_DEBUG_EVENT( options, reload_buildings_config )

    ADD_DEBUG_EVENT( draw, toggle_grid_visibility )
    ADD_DEBUG_EVENT( draw, toggle_overlay_base )
    ADD_DEBUG_EVENT( draw, toggle_show_path )
    ADD_DEBUG_EVENT( draw, toggle_show_roads )
    ADD_DEBUG_EVENT( draw, toggle_show_buildings )
    ADD_DEBUG_EVENT( draw, toggle_show_trees )
    ADD_DEBUG_EVENT( draw, toggle_show_object_area )
    ADD_DEBUG_EVENT( draw, toggle_show_walkable_tiles )
    ADD_DEBUG_EVENT( draw, toggle_show_locked_tiles )
    ADD_DEBUG_EVENT( draw, toggle_show_flat_tiles )
    ADD_DEBUG_EVENT( draw, toggle_show_rocks )

    ADD_DEBUG_EVENT( empiremap, toggle_show_empireMapTiles )

    ADD_DEBUG_EVENT( steam, reset_steam_prefs ) */
}
