(include "/map/cwfs_scripts.inc")
{helpers
	{modifiers
			{"file"
				{name "/map/damaged_range.mod"}
			}
	}
	{triggers
		{"service/kaz/kaz_enable"
			{autoreset}
			{condition
				{terms
					{"1.entities"
						{selector
							{tag low_speed_bullet}
						}
					}
					{"2.entities"
						{selector
							{source advanced}
							{group
								{include
									{prop
										{prop kaz}
									}
									{state
										{state operatable}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{tag low_speed_bullet}
					}
					{tag_remove low_speed_bullet}
				}
				{"effect"
					{selector
						{source advanced}
						{group
							{include
								{prop
									{prop kaz}
								}
								{state
									{state inhabited}
								}
							}
						}
					}
					{effect kaz_work}
				}
			}
		}
		{"service/kaz/kaz_enable1"
			{autoreset}
			{condition
				{terms
					{"1.entities"
						{selector
							{tag low_speed_bullet}
						}
					}
					{"2.entities"
						{selector
							{source advanced}
							{group
								{include
									{prop
										{prop kaz}
									}
									{state
										{state operatable}
									}
								}
							}
						}
					}
					{"3.entities"
						{selector
							{source advanced}
							{group
								{include
									{prop
										{prop kaz}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag kaz_working}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{tag low_speed_bullet}
					}
					{tag_remove low_speed_bullet}
				}
				{"effect"
					{selector
						{source advanced}
						{group
							{include
								{prop
									{prop kaz}
								}
								{state
									{state inhabited}
								}
							}
						}
					}
					{effect kaz_work}
				}
			}
		}
			{"service/cw_autotakeoff"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop cw_autotakeoff}
										}
									}
									{exclude
										{tag
											{tag cw_autotakeoff_activated}
										}
									}
								}
							}
						}
					}
				}
				{actions
					{"air_state"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop cw_autotakeoff}
									}
								}
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
									{prop
										{prop shahed136}
									}
								}
							}
						}
						{altitude 35}
					}
					{"air_state"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop shahed136}
									}
								}
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
								}
							}
						}
						{altitude 3}
					}
					{"action"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop cw_autotakeoff}
									}
								}
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
								}
							}
						}
						{action move}
						{target
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
									{prop
										{prop cw_autotakeoff}
									}
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop cw_autotakeoff}
											}
										}
										{exclude
											{tag
												{tag cw_autotakeoff_activated}
											}
										}
									}
								}
							}
						}
					}
					{"actor_state"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop cw_autotakeoff}
									}
								}
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
								}
							}
						}
						{control user}
					}
					{"entity_state"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop cw_autotakeoff}
									}
								}
								{exclude
									{tag
										{tag cw_autotakeoff_activated}
									}
								}
							}
						}
						{tag_add cw_autotakeoff_activated}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/cw_autotakeoff"}
					}
				}
			}
			{"service/paradrop/0"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop0}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute0}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop0}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop0}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute0}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop0}
						}
						{tag_remove heli_paradrop0}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/0"}
					}
				}
			}
			{"service/paradrop/0_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop0}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop0}
						}
						{tag_remove heli_paradrop0}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/0_"}
					}
				}
			}
			{"service/paradrop/1"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop1}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute1}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop1}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop1}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute1}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop1}
						}
						{tag_remove heli_paradrop1}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/1"}
					}
				}
			}
			{"service/paradrop/2"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop2}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute2}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop2}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop2}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute2}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop2}
						}
						{tag_remove heli_paradrop2}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/2"}
					}
				}
			}
			{"service/paradrop/3"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop3}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute3}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop3}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop3}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute3}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop3}
						}
						{tag_remove heli_paradrop3}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/3"}
					}
				}
			}
			{"service/paradrop/4"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop4}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute4}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop4}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop4}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute4}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop4}
						}
						{tag_remove heli_paradrop4}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/4"}
					}
				}
			}
			{"service/paradrop/5"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop5}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute5}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop5}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop5}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute5}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop5}
						}
						{tag_remove heli_paradrop5}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/5"}
					}
				}
			}
			{"service/paradrop/6"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop6}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute6}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop6}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop6}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute6}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop6}
						}
						{tag_remove heli_paradrop6}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/6"}
					}
				}
			}
			{"service/paradrop/7"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop7}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{group
								{select
									{tag
										{tag heli_parashute7}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{tag heli_paradrop7}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{group
								{select
									{tag
										{tag heli_paradrop7}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{tag heli_parashute7}
								}
							}
						}
					}
					{"entity_state"
						{selector
							{tag heli_paradrop7}
						}
						{tag_remove heli_paradrop7}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/7"}
					}
				}
			}
			{"service/paradrop/1_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop1}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop1}
						}
						{tag_remove heli_paradrop1}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/1_"}
					}
				}
			}
			{"service/paradrop/2_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop2}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop2}
						}
						{tag_remove heli_paradrop2}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/2_"}
					}
				}
			}
			{"service/paradrop/3_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop3}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop3}
						}
						{tag_remove heli_paradrop3}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/3_"}
					}
				}
			}
			{"service/paradrop/4_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop4}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop4}
						}
						{tag_remove heli_paradrop4}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/4_"}
					}
				}
			}
			{"service/paradrop/5_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop5}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop5}
						}
						{tag_remove heli_paradrop5}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/5_"}
					}
				}
			}
			{"service/paradrop/6_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop6}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop6}
						}
						{tag_remove heli_paradrop6}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/6_"}
					}
				}
			}
			{"service/paradrop/7_"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{tag heli_paradrop7}
							}
							{count
								{op ">"}
								{value 1}
							}
						}
					}
				}
				{actions
					{"entity_state"
						{selector
							{tag heli_paradrop7}
						}
						{tag_remove heli_paradrop7}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/7_"}
					}
				}
			}
			{"service/paradrop/vdv/2_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place2}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place2}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place2}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place2}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place2}
								}
							}
						}
						{place
							{type specific}
							{name vehicle2}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/2_link"}
					}
				}
			}
			{"service/paradrop/vdv/1_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place1}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place1}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place1}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place1}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place1}
								}
							}
						}
						{place
							{type specific}
							{name vehicle1}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/1_link"}
					}
				}
			}
			{"service/paradrop/vdv/3_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place3}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place3}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place3}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place3}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place3}
								}
							}
						}
						{place
							{type specific}
							{name vehicle3}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/3_link"}
					}
				}
			}
			{"service/paradrop/vdv/4_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place4}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place4}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place4}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place4}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place4}
								}
							}
						}
						{place
							{type specific}
							{name vehicle4}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/4_link"}
					}
				}
			}
			{"service/paradrop/vdv/5_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place5}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place5}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place5}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place5}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place5}
								}
							}
						}
						{place
							{type specific}
							{name vehicle5}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/5_link"}
					}
				}
			}
			{"service/paradrop/vdv/6_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place6}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place6}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place6}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place6}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place6}
								}
							}
						}
						{place
							{type specific}
							{name vehicle6}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/6_link"}
					}
				}
			}
			{"service/paradrop/vdv/7_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place7}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place7}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place7}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place7}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place7}
								}
							}
						}
						{place
							{type specific}
							{name vehicle7}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/7_link"}
					}
				}
			}
			{"service/paradrop/vdv/8_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place8}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place8}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place8}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place8}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place8}
								}
							}
						}
						{place
							{type specific}
							{name vehicle8}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/8_link"}
					}
				}
			}
			{"service/paradrop/vdv/9_link"
				{autoreset}
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag vdv_link_place9}
							}
							{count
								{op "=="}
								{value 1}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_place9}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{select
											{tag
												{tag vdv_link_place9}
											}
										}
									}
								}
							}
							{amount 1
							}
						}
						{entities
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag vdv_link_to_place9}
									}
								}
								{exclude
									{state
										{state linked}
									}
								}
							}
							{amount 1
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag vdv_link_place9}
								}
							}
						}
						{place
							{type specific}
							{name vehicle9}
						}
					}
					{"delay"
						{time 0.01}
					}
					{"trigger"
						{name "service/paradrop/vdv/9_link"}
					}
				}
			}
			{"service/paradrop/vdv/unlink"
				{condition
					{terms
						{"1.entities"
							{selector
								{ignore_captured_by_user 0}
								{tag unlink_me}
							}
						}
					}
				}
				{actions
					{"linker"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop vehicle}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{ignore_captured_by_user 0}
									{tag unlink_me}
								}
							}
						}
						{action unlink}
						{entities
							{ignore_captured_by_user 0}
							{tag unlink_me}
						}
					}
					{"entity_state"
						{selector
							{ignore_captured_by_user 0}
							{tag unlink_me}
						}
						{tag_remove unlink_me}
					}
					{"delay"
						{time 0.2}
					}
					{"trigger"
						{name "service/paradrop/vdv/unlink"}
					}
				}
			}

		{"service/hovering/set_speed1"
			{autoreset}
			{condition
				{terms
					{"1.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag cwhs_speed_60}
									}
									{tag
										{tag cwhs_speed_55}
									}
									{tag
										{tag cwhs_speed_50}
									}
									{tag
										{tag cwhs_speed_45}
									}
									{tag
										{tag cwhs_speed_40}
									}
									{tag
										{tag cwhs_speed_35}
									}
									{tag
										{tag cwhs_speed_30}
									}
									{tag
										{tag cwhs_speed_20}
									}
									{tag
										{tag cwhs_speed_10}
									}
									{tag
										{tag cwhs_speed_1}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_60}
								}
							}
						}
					}
					{movement
						{speed_kph 60}
						{max_speed_kph 60}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_60}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_60}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_55}
								}
							}
						}
					}
					{movement
						{speed_kph 55}
						{max_speed_kph 55}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_55}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_55}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_50}
								}
							}
						}
					}
					{movement
						{speed_kph 50}
						{max_speed_kph 50}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_50}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_50}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_45}
								}
							}
						}
					}
					{movement
						{speed_kph 45}
						{max_speed_kph 45}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_45}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_45}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_40}
								}
							}
						}
					}
					{movement
						{speed_kph 40}
						{max_speed_kph 40}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_40}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_40}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_35}
								}
							}
						}
					}
					{movement
						{speed_kph 35}
						{max_speed_kph 35}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_35}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_35}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_30}
								}
							}
						}
					}
					{movement
						{speed_kph 30}
						{max_speed_kph 30}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_30}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_30}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_20}
								}
							}
						}
					}
					{movement
						{speed_kph 20}
						{max_speed_kph 20}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_20}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_20}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_10}
								}
							}
						}
					}
					{movement
						{speed_kph 10}
						{max_speed_kph 10}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_10}
					}
					{tag_add cwhs_speed_changed}
					{tag_remove cwhs_speed_10}
				}
				{"actor_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_speed_1}
								}
							}
						}
					}
					{movement
						{speed_kph 1}
						{max_speed_kph 1}
					}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag cwhs_speed_1}
					}
					{tag_add cwhs_hovering}
					{tag_remove cwhs_speed_1}
				}
				{"delay"
					{time 0.3}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag cwhs_accelerate_me}
								}
								{tag
									{tag cwhs_deccelerate_me}
								}
							}
						}
					}
					{effect cwhs_change_speed}
				}
				{"trigger"
					{name "service/hovering/set_speed1"}
				}
			}
		}
		
		{"service/smalluav/eleron/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop smalluav_rus_control}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
						}
						{distance 340}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_rus_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus_control}
								}
								{state
									{state "operatable inhabited"}
								}
							}
							{exclude
								{tag
									{tag hidden}
								}
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop smalluav_rus}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/eleron/loose_control"}
				}
			}
		}
		{"service/smalluav/eleron/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
						}
						{distance 330}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_rus_control}
										}
										{state
											{state operatable}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/eleron/regain_control"}
				}
			}
		}
		{"service/smalluav/eleron/return"
			{autoreset}
			{condition
				{terms
					{"2.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag smalluav_return}
									}
								}
								{include
									{prop
										{prop smalluav_rus}
									}
								}
								{exclude
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{altitude 30}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
								{tag
									{tag smalluav_return}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus_control}
								}
								{state
									{state "operatable inhabited"}
								}
							}
							{exclude
								{tag
									{tag hidden}
								}
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_return}
										}
										{prop
											{prop smalluav_rus}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag ally}
								}
								{tag
									{tag destroyed}
								}
							}
						}
					}
					{tag_add smalluav_land}
					{tag_remove smalluav_return}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/eleron/return"}
				}
			}
		}
		{"service/smalluav/eleron/land"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus}
									}
									{tag
										{tag smalluav_land}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_rus_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
						}
						{distance 70}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_land}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{state
									{state inactive}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_rus_control}
										}
										{state
											{state operatable}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{ground}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_rus}
								}
								{tag
									{tag smalluav_land}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_rus_control}
										}
										{state
											{state operatable}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_land}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/eleron/land"}
				}
			}
		}
		{"service/smalluav/raven/land"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_usa}
									}
									{tag
										{tag smalluav_land}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "rq11_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 70}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_land}
								}
							}
							{include
								{prop
									{prop smalluav_usa}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{state
									{state inactive}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{ground}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
								{tag
									{tag smalluav_land}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_land}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/raven/land"}
				}
			}
		}
		{"service/smalluav/raven/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_usa}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "rq11_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "rq11_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 190}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "rq11_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop smalluav_usa}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/raven/loose_control"}
				}
			}
		}
		{"service/smalluav/raven/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_usa}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "rq11_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 180}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/raven/regain_control"}
				}
			}
		}
		{"service/smalluav/raven/return"
			{autoreset}
			{condition
				{terms
					{"2.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag smalluav_return}
									}
								}
								{include
									{prop
										{prop smalluav_usa}
									}
								}
								{exclude
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{altitude 30}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa}
								}
								{tag
									{tag smalluav_return}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "rq11_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_return}
										}
										{prop
											{prop smalluav_usa}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_usa}
								}
							}
							{exclude
								{tag
									{tag ally}
								}
								{tag
									{tag destroyed}
								}
							}
						}
					}
					{tag_add smalluav_land}
					{tag_remove smalluav_return}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/raven/return"}
				}
			}
		}
		{"service/smalluav/aladin/land"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop aladin}
									}
									{tag
										{tag smalluav_land}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "aladin_anten"}
									}
									{with_item
										{type existance}
										{item "aladin_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 70}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_land}
								}
							}
							{include
								{prop
									{prop aladin}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{state
									{state inactive}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "aladin_anten"}
										}
										{with_item
											{type existance}
											{item "aladin_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{ground}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
								{tag
									{tag smalluav_land}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "aladin_anten"}
										}
										{with_item
											{type existance}
											{item "aladin_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_land}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/aladin/land"}
				}
			}
		}
		{"service/smalluav/aladin/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop aladin}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "aladin_anten"}
											}
											{with_item
												{type existance}
												{item "aladin_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "aladin_anten"}
									}
									{with_item
										{type existance}
										{item "aladin_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 220}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "aladin_anten"}
										}
										{with_item
											{type existance}
											{item "aladin_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "aladin_anten"}
								}
								{with_item
									{type existance}
									{item "aladin_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop aladin}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/aladin/loose_control"}
				}
			}
		}
		{"service/smalluav/aladin/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop aladin}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "aladin_anten"}
									}
									{with_item
										{type existance}
										{item "aladin_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 210}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "aladin_anten"}
										}
										{with_item
											{type existance}
											{item "aladin_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/aladin/regain_control"}
				}
			}
		}
		{"service/smalluav/aladin/return"
			{autoreset}
			{condition
				{terms
					{"2.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag smalluav_return}
									}
								}
								{include
									{prop
										{prop aladin}
									}
								}
								{exclude
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{altitude 30}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop aladin}
								}
								{tag
									{tag smalluav_return}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "aladin_anten"}
								}
								{with_item
									{type existance}
									{item "aladin_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_return}
										}
										{prop
											{prop aladin}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop aladin}
								}
							}
							{exclude
								{tag
									{tag ally}
								}
								{tag
									{tag destroyed}
								}
							}
						}
					}
					{tag_add smalluav_land}
					{tag_remove smalluav_return}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/aladin/return"}
				}
			}
		}
		{"service/smalluav/smalluav_cn/land"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_cn}
									}
									{tag
										{tag smalluav_land}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "type06h_uav"}
									}
									{with_item
										{type existance}
										{item "smalluav_cn_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
							{group
								{include
									{prop
										{prop smalluav_cn_control}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 70}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_land}
								}
							}
							{include
								{prop
									{prop smalluav_cn}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{state
									{state inactive}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "type06h_uav"}
										}
										{with_item
											{type existance}
											{item "smalluav_cn_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
								{group
									{include
										{prop
											{prop smalluav_cn_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{ground}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
								{tag
									{tag smalluav_land}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "type06h_uav"}
										}
										{with_item
											{type existance}
											{item "smalluav_cn_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
								{group
									{include
										{prop
											{prop smalluav_cn_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_land}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_cn/land"}
				}
			}
		}
		{"service/smalluav/smalluav_cn/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_cn}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "type06h_uav"}
											}
											{with_item
												{type existance}
												{item "smalluav_cn_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
									{group
										{include
											{prop
												{prop smalluav_cn_control}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "type06h_uav"}
									}
									{with_item
										{type existance}
										{item "smalluav_cn_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
							{group
								{include
									{prop
										{prop smalluav_cn_control}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 220}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "type06h_uav"}
										}
										{with_item
											{type existance}
											{item "smalluav_cn_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
								{group
									{include
										{prop
											{prop smalluav_cn_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "type06h_uav"}
								}
								{with_item
									{type existance}
									{item "smalluav_cn_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{group
							{include
								{prop
									{prop smalluav_cn_control}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop smalluav_cn}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_cn/loose_control"}
				}
			}
		}
		{"service/smalluav/smalluav_cn/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_cn}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "type06h_uav"}
									}
									{with_item
										{type existance}
										{item "smalluav_cn_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
							{group
								{include
									{prop
										{prop smalluav_cn_control}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 210}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "type06h_uav"}
										}
										{with_item
											{type existance}
											{item "smalluav_cn_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
								{group
									{include
										{prop
											{prop smalluav_cn_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_cn/regain_control"}
				}
			}
		}
		{"service/smalluav/smalluav_cn/return"
			{autoreset}
			{condition
				{terms
					{"2.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag smalluav_return}
									}
								}
								{include
									{prop
										{prop smalluav_cn}
									}
								}
								{exclude
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_rus}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{altitude 30}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_cn}
								}
								{tag
									{tag smalluav_return}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "type06h_uav"}
								}
								{with_item
									{type existance}
									{item "smalluav_cn_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{group
							{include
								{prop
									{prop smalluav_cn_control}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_return}
										}
										{prop
											{prop smalluav_cn}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_cn}
								}
							}
							{exclude
								{tag
									{tag ally}
								}
								{tag
									{tag destroyed}
								}
							}
						}
					}
					{tag_add smalluav_land}
					{tag_remove smalluav_return}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_cn/return"}
				}
			}
		}
		{"service/smalluav/uran9/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop uran9}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop uran_control}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{state
												{state inactive}
											}
										}
									}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "uran_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop uran_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "uran_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 120}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran9}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop uran_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "uran_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran9}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran_control}
								}
								{state
									{state "operatable inhabited"}
								}
							}
							{exclude
								{tag
									{tag hidden}
								}
								{state
									{state inactive}
								}
							}
						}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "uran_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop uran9}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/uran9/loose_control"}
				}
			}
		}
		{"service/smalluav/uran9/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop uran9}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop uran_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "uran_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 110}
					}
				}
			}
			{actions
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran9}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop uran_control}
										}
										{state
											{state inhabited}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "uran_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
					}
					{drop orders}
					{action cancel}
					{target
						{ignore_captured_by_user 0}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran9}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop uran_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "uran_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop uran9}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/uran9/regain_control"}
				}
			}
		}
		{"service/smalluav/exactor/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop exactor}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop exactor_control}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{broken_components
												{masks
													"gunner_panel"
												}
											}
										}
									}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "exactor_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop exactor_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{broken_components
										{masks
											"gunner_panel"
										}
									}
								}
							}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "exactor_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 50}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop exactor}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop exactor_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{broken_components
											{masks
												"gunner_panel"
											}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "exactor_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect update_gun23}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/exactor/loose_control"}
				}
			}
		}
		{"service/smalluav/exactor/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop exactor}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop exactor_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{broken_components
										{masks
											"gunner_panel"
										}
									}
								}
							}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "exactor_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 45}
					}
				}
			}
			{actions
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop exactor}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop exactor_control}
										}
										{state
											{state inhabited}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{broken_components
											{masks
												"gunner_panel"
											}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "exactor_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
					}
					{drop orders}
					{action cancel}
					{target
						{ignore_captured_by_user 0}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop exactor}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop exactor_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{broken_components
											{masks
												"gunner_panel"
											}
										}
									}
								}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "exactor_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop exactor}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{add select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop exactor}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect update_gun23}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/exactor/regain_control"}
				}
			}
		}
		{"service/smalluav/smalluav_irn/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_irn}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop smalluav_irn_control}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_irn_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
						}
						{distance 410}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_irn_control}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{order eAdvance
								}
								{order eMoveTask
								}
								{order eAttack
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn_control}
								}
								{state
									{state "operatable inhabited"}
								}
							}
							{exclude
								{tag
									{tag hidden}
								}
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop smalluav_irn}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_irn/loose_control"}
				}
			}
		}
		{"service/smalluav/smalluav_irn/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_irn}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_irn_control}
									}
									{state
										{state "operatable inhabited"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
								}
							}
						}
						{distance 400}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop smalluav_irn_control}
										}
										{state
											{state operatable}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_irn/regain_control"}
				}
			}
		}
		{"service/smalluav/smalluav_irn/return"
			{autoreset}
			{condition
				{terms
					{"2.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag smalluav_return}
									}
								}
								{include
									{prop
										{prop smalluav_irn}
									}
								}
								{exclude
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"air_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_irn}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{altitude 30}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
								{tag
									{tag smalluav_return}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_irn_control}
								}
								{state
									{state "operatable inhabited"}
								}
							}
							{exclude
								{tag
									{tag hidden}
								}
								{state
									{state inactive}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_return}
										}
										{prop
											{prop smalluav_irn}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_return}
								}
							}
							{include
								{prop
									{prop smalluav_irn}
								}
							}
							{exclude
								{tag
									{tag ally}
								}
								{tag
									{tag destroyed}
								}
							}
						}
					}
					{tag_add smalluav_land}
					{tag_remove smalluav_return}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_irn/return"}
				}
			}
		}
		{"service/smalluav/smalluav_irn/assign_target"
			{condition
				{terms
					{"1.entities"
						{selector
							{source advanced}
							{group
								{include
									{prop
										{prop smalluav_irn}
									}
								}
								{exclude
									{tag
										{tag target_assigned}
									}
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"delay"
					{time 1}
				}
				{"entity_state"
					{selector
						{source advanced}
						{group
							{include
								{prop
									{prop smalluav_irn}
								}
							}
							{exclude
								{tag
									{tag target_assigned}
								}
								{state
									{state inactive}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add smalluav_irn_current}
				}
				{"action"
					{selector
						{tag smalluav_irn_current}
					}
					{drop orders}
					{action attack_ground}
					{target
						{source advanced}
						{group
							{select
								{tag
									{tag cwps_ground_attack}
								}
							}
							{include
								{tag
									{tag rus_target_other}
								}
							}
							{exclude
								{tag
									{tag target_assigned}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{tag smalluav_irn_current}
							}
						}
					}
				}
				{"entity_state"
					{selector
						{source advanced}
						{group
							{select
								{tag
									{tag cwps_ground_attack}
								}
							}
							{include
								{tag
									{tag rus_target_other}
								}
							}
							{exclude
								{tag
									{tag target_assigned}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{tag smalluav_irn_current}
							}
						}
						{amount 1
						}
					}
					{tag_add target_assigned}
				}
				{"entity_state"
					{selector
						{tag smalluav_irn_current}
					}
					{tag_add target_assigned}
					{tag_remove smalluav_irn_current}
				}
				{"delay"
					{time 0.1}
				}
				{"trigger"
					{name "service/smalluav/smalluav_irn/assign_target"}
				}
			}
		}
		{"service/smalluav/smalluav_usa_40km/loose_control"
			{autoreset}
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_usa_40km}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop human}
											}
											{with_item
												{type existance}
												{item "rq11_control"}
											}
										}
										{exclude
											{state
												{state inactive}
											}
											{tag
												{tag hidden}
											}
											{state
												{state dead}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "rq11_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 340}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa_40km}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 2}
				}
				{"action"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa_40km}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{drop orders}
					{action move}
					{target
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop human}
								}
								{with_item
									{type existance}
									{item "rq11_control"}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag hidden}
								}
								{state
									{state dead}
								}
							}
						}
						{amount 1
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{tag
											{tag smalluav_no_connect}
										}
										{prop
											{prop smalluav_usa_40km}
										}
									}
									{exclude
										{tag
											{tag destroyed}
										}
										{tag
											{tag ally}
										}
									}
								}
							}
						}
					}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_usa_40km/loose_control"}
				}
			}
		}
		{"service/smalluav/smalluav_usa_40km/regain_control"
			{autoreset}
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop smalluav_usa_40km}
									}
									{tag
										{tag smalluav_no_connect}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
									{tag
										{tag uav_jammed}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop human}
									}
									{with_item
										{type existance}
										{item "rq11_control"}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag hidden}
									}
									{state
										{state dead}
									}
								}
							}
						}
						{distance 330}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa_40km}
								}
								{tag
									{tag smalluav_no_connect}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop human}
										}
										{with_item
											{type existance}
											{item "rq11_control"}
										}
									}
									{exclude
										{state
											{state inactive}
										}
										{tag
											{tag hidden}
										}
										{state
											{state dead}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_remove smalluav_no_connect}
				}
				{"ables"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop smalluav_usa_40km}
								}
							}
							{exclude
								{tag
									{tag destroyed}
								}
								{tag
									{tag ally}
								}
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag uav_jammed}
								}
							}
						}
					}
					{add select}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/smalluav/smalluav_usa_40km/regain_control"}
				}
			}
		}


		{"service/ecm/rus/jam400"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_1}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 400}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_1}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_1_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_current}
					}
					{tag_add ecm_effect_1}
				}
				{"effect"
					{selector
						{tag ecm_effect_1_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_current}
					}
					{tag_remove ecm_effect_1_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam400"}
				}
			}
		}
		{"service/ecm/rus/jam400_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_1}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 410}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_1}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_1_off_current}
					{tag_remove ecm_effect_1}
				}
				{"effect"
					{selector
						{tag ecm_effect_1_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_off_current}
					}
					{tag_remove ecm_effect_1_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam400_off"}
				}
			}
		}
		{"service/ecm/usa/jam400"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_1}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 400}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_1}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_1_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_current}
					}
					{tag_add ecm_effect_1}
				}
				{"effect"
					{selector
						{tag ecm_effect_1_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_current}
					}
					{tag_remove ecm_effect_1_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam400"}
				}
			}
		}
		{"service/ecm/usa/jam400_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_1}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 410}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_1}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_1_off_current}
					{tag_remove ecm_effect_1}
				}
				{"effect"
					{selector
						{tag ecm_effect_1_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_1_off_current}
					}
					{tag_remove ecm_effect_1_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam400_off"}
				}
			}
		}
		{"service/ecm/rus/jam300"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_2}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 300}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_2}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_2_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_current}
					}
					{tag_add ecm_effect_2}
				}
				{"effect"
					{selector
						{tag ecm_effect_2_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_current}
					}
					{tag_remove ecm_effect_2_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam300"}
				}
			}
		}
		{"service/ecm/rus/jam300_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_2}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 310}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_2}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_2_off_current}
					{tag_remove ecm_effect_2}
				}
				{"effect"
					{selector
						{tag ecm_effect_2_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_off_current}
					}
					{tag_remove ecm_effect_2_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam300_off"}
				}
			}
		}
		{"service/ecm/usa/jam300"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_2}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 300}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_2}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_2_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_current}
					}
					{tag_add ecm_effect_2}
				}
				{"effect"
					{selector
						{tag ecm_effect_2_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_current}
					}
					{tag_remove ecm_effect_2_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam300"}
				}
			}
		}
		{"service/ecm/usa/jam300_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_2}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 310}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_2}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_2_off_current}
					{tag_remove ecm_effect_2}
				}
				{"effect"
					{selector
						{tag ecm_effect_2_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_2_off_current}
					}
					{tag_remove ecm_effect_2_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam300_off"}
				}
			}
		}
		{"service/ecm/rus/jam200"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_3}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 200}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_3}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_3_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_current}
					}
					{tag_add ecm_effect_3}
				}
				{"effect"
					{selector
						{tag ecm_effect_3_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_current}
					}
					{tag_remove ecm_effect_3_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam200"}
				}
			}
		}
		{"service/ecm/rus/jam200_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_3}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 210}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_3}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_3_off_current}
					{tag_remove ecm_effect_3}
				}
				{"effect"
					{selector
						{tag ecm_effect_3_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_off_current}
					}
					{tag_remove ecm_effect_3_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam200_off"}
				}
			}
		}
		{"service/ecm/usa/jam200"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_3}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 200}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_3}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_3_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_current}
					}
					{tag_add ecm_effect_3}
				}
				{"effect"
					{selector
						{tag ecm_effect_3_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_current}
					}
					{tag_remove ecm_effect_3_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam200"}
				}
			}
		}
		{"service/ecm/usa/jam200_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_3}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 210}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_3}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_3_off_current}
					{tag_remove ecm_effect_3}
				}
				{"effect"
					{selector
						{tag ecm_effect_3_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_3_off_current}
					}
					{tag_remove ecm_effect_3_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam200_off"}
				}
			}
		}
		{"service/ecm/rus/jam150"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_4}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 150}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_4}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_4_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_current}
					}
					{tag_add ecm_effect_4}
				}
				{"effect"
					{selector
						{tag ecm_effect_4_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_current}
					}
					{tag_remove ecm_effect_4_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam150"}
				}
			}
		}
		{"service/ecm/rus/jam150_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_4}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 160}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_4}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_4_off_current}
					{tag_remove ecm_effect_4}
				}
				{"effect"
					{selector
						{tag ecm_effect_4_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_off_current}
					}
					{tag_remove ecm_effect_4_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam150_off"}
				}
			}
		}
		{"service/ecm/usa/jam150"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_4}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 150}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_4}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_4_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_current}
					}
					{tag_add ecm_effect_4}
				}
				{"effect"
					{selector
						{tag ecm_effect_4_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_current}
					}
					{tag_remove ecm_effect_4_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam150"}
				}
			}
		}
		{"service/ecm/usa/jam150_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_4}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 160}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_4}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_4_off_current}
					{tag_remove ecm_effect_4}
				}
				{"effect"
					{selector
						{tag ecm_effect_4_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_4_off_current}
					}
					{tag_remove ecm_effect_4_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam150_off"}
				}
			}
		}
		{"service/ecm/rus/jam100"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_5}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 100}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_5}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_5_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_current}
					}
					{tag_add ecm_effect_5}
				}
				{"effect"
					{selector
						{tag ecm_effect_5_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_current}
					}
					{tag_remove ecm_effect_5_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam100"}
				}
			}
		}
		{"service/ecm/rus/jam100_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_5}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 110}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_5}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_5_off_current}
					{tag_remove ecm_effect_5}
				}
				{"effect"
					{selector
						{tag ecm_effect_5_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_off_current}
					}
					{tag_remove ecm_effect_5_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam100_off"}
				}
			}
		}
		{"service/ecm/usa/jam100"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_5}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 100}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_5}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_5_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_current}
					}
					{tag_add ecm_effect_5}
				}
				{"effect"
					{selector
						{tag ecm_effect_5_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_current}
					}
					{tag_remove ecm_effect_5_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam100"}
				}
			}
		}
		{"service/ecm/usa/jam100_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_5}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 110}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_5}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_5_off_current}
					{tag_remove ecm_effect_5}
				}
				{"effect"
					{selector
						{tag ecm_effect_5_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_5_off_current}
					}
					{tag_remove ecm_effect_5_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam100_off"}
				}
			}
		}
		{"service/ecm/rus/jam50"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_6}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 50}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_6}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_6_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_current}
					}
					{tag_add ecm_effect_6}
				}
				{"effect"
					{selector
						{tag ecm_effect_6_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_current}
					}
					{tag_remove ecm_effect_6_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam50"}
				}
			}
		}
		{"service/ecm/rus/jam50_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_6}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_rus}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 60}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_usa}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_6}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_rus}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_6_off_current}
					{tag_remove ecm_effect_6}
				}
				{"effect"
					{selector
						{tag ecm_effect_6_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_off_current}
					}
					{tag_remove ecm_effect_6_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/rus/jam50_off"}
				}
			}
		}
		{"service/ecm/usa/jam50"
			{condition
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_vulnerable_rus}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_effect_6}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 50}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_effect_6}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_6_current}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_current}
					}
					{tag_add ecm_effect_6}
				}
				{"effect"
					{selector
						{tag ecm_effect_6_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_current}
					}
					{tag_remove ecm_effect_6_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam50"}
				}
			}
		}
		{"service/ecm/usa/jam50_off"
			{condition
				{expression "!1"}
				{terms
					{"1.near"
						{units
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{state
										{state operatable}
									}
									{tag
										{tag ecm_effect_6}
									}
								}
								{exclude
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ecm_invulnerable}
									}
								}
							}
							{sort
								{type entity}
								{entity
									{source advanced}
									{ignore_captured_by_user 0}
									{group
										{include
											{prop
												{prop ecm_station_usa}
											}
											{state
												{state operatable}
											}
										}
										{exclude
											{tag
												{tag no_power}
											}
											{tag
												{tag radar_off}
											}
											{tag
												{tag destroyed}
											}
											{state
												{state inactive}
											}
										}
									}
								}
								{mode farthest}
							}
							{amount 1
							}
						}
						{near_to
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{include
									{prop
										{prop ecm_station_usa}
									}
									{state
										{state operatable}
									}
								}
								{exclude
									{tag
										{tag no_power}
									}
									{tag
										{tag radar_off}
									}
									{tag
										{tag destroyed}
									}
									{state
										{state inactive}
									}
								}
							}
						}
						{distance 60}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{include
								{prop
									{prop ecm_vulnerable_rus}
								}
								{state
									{state operatable}
								}
								{tag
									{tag ecm_effect_6}
								}
							}
							{exclude
								{state
									{state inactive}
								}
								{tag
									{tag destroyed}
								}
								{tag
									{tag ecm_invulnerable}
								}
							}
						}
						{sort
							{type entity}
							{entity
								{source advanced}
								{ignore_captured_by_user 0}
								{group
									{include
										{prop
											{prop ecm_station_usa}
										}
										{state
											{state operatable}
										}
									}
									{exclude
										{tag
											{tag no_power}
										}
										{tag
											{tag radar_off}
										}
										{tag
											{tag destroyed}
										}
										{state
											{state inactive}
										}
									}
								}
							}
							{mode farthest}
						}
						{amount 1
						}
					}
					{tag_add ecm_effect_6_off_current}
					{tag_remove ecm_effect_6}
				}
				{"effect"
					{selector
						{tag ecm_effect_6_off_current}
					}
					{effect ecm_jammed}
				}
				{"entity_state"
					{selector
						{ignore_captured_by_user 0}
						{tag ecm_effect_6_off_current}
					}
					{tag_remove ecm_effect_6_off_current}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/usa/jam50_off"}
				}
			}
		}
		{"service/ecm/uav_jammed"
			{autoreset}
			{condition
				{terms
					{"1.entities"
						{selector
							{source advanced}
							{ignore_captured_by_user 0}
							{group
								{select
									{tag
										{tag uav_jammed}
									}
								}
								{exclude
									{tag
										{tag smalluav_no_connect}
									}
									{state
										{state inactive}
									}
									{tag
										{tag destroyed}
									}
									{tag
										{tag ally}
									}
								}
							}
						}
					}
				}
			}
			{actions
				{"entity_state"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag uav_jammed}
								}
							}
							{exclude
								{tag
									{tag smalluav_no_connect}
								}
								{tag
									{tag destroyed}
								}
								{state
									{state inactive}
								}
								{tag
									{tag ally}
								}
							}
						}
					}
					{tag_add smalluav_no_connect}
				}
				{"ables"
					{selector
						{ignore_captured_by_user 0}
						{tag smalluav_no_connect}
					}
					{remove select}
				}
				{"effect"
					{selector
						{source advanced}
						{ignore_captured_by_user 0}
						{group
							{select
								{tag
									{tag smalluav_no_connect}
								}
							}
						}
					}
					{effect reset_manual_control}
				}
				{"delay"
					{time 0.5}
				}
				{"trigger"
					{name "service/ecm/uav_jammed"}
				}
			}
		}
		{"service/reset_scripts"
			{condition
			}
			{actions
				{"delay"
					{time 90}
				}
				{"trigger"
					{name "service/cw_autotakeoff"}
				}
				{"trigger"
					{name "service/paradrop/vdv/1_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/2_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/3_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/4_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/5_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/6_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/7_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/8_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/9_link"}
				}
				{"trigger"
					{name "service/paradrop/vdv/unlink"}
				}
				{"delay"
					{time 1}
				}
				{"trigger"
					{name "service/reset_scripts"}
				}
			}
		}
	}
}
