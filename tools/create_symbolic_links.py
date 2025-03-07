#
# Copyright(c) 2022 Intel. Licensed under the MIT License <http://opensource.org/licenses/MIT>.
#

import argparse
import json
import os
import spear


if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("--unreal_engine_dir", required=True)
    parser.add_argument("--unreal_project_dir", default=os.path.realpath(os.path.join(os.path.dirname(__file__), "..", "cpp", "unreal_projects", "SpearSim")))
    parser.add_argument("--unreal_plugins_dir", default=os.path.realpath(os.path.join(os.path.dirname(__file__), "..", "cpp", "unreal_plugins")))
    parser.add_argument("--third_party_dir", default=os.path.realpath(os.path.join(os.path.dirname(__file__), "..", "third_party")))
    args = parser.parse_args()

    assert os.path.exists(args.unreal_engine_dir)
    assert os.path.exists(args.unreal_project_dir)
    assert os.path.exists(args.unreal_plugins_dir)
    assert os.path.exists(args.third_party_dir)

    starter_content_dir = os.path.realpath(os.path.join(args.unreal_engine_dir, "Samples", "StarterContent", "Content", "StarterContent"))
    unreal_project_dir  = os.path.realpath(args.unreal_project_dir)
    unreal_plugins_dir  = os.path.realpath(args.unreal_plugins_dir)
    third_party_dir     = os.path.realpath(args.third_party_dir)

    assert os.path.exists(starter_content_dir)

    unreal_plugins = os.listdir(unreal_plugins_dir)

    # for each plugin...
    for plugin in unreal_plugins:

        # ...if the plugin is a valid plugin (i.e., plugin dir has a uplugin file)
        uplugin = os.path.realpath(os.path.join(unreal_plugins_dir, plugin, plugin + ".uplugin"))
        if os.path.exists(uplugin):

            print(f"[SPEAR | create_sybmolic_links.py] Found uplugin: {uplugin}")

            # create a symlink to third_party
            symlink_third_party_dir = os.path.join(unreal_plugins_dir, plugin, "ThirdParty") # don't want os.path.realpath here
            if spear.path_exists(symlink_third_party_dir):
                print(f"[SPEAR | create_sybmolic_links.py]     File or directory or symlink exists, removing: {symlink_third_party_dir}")
                spear.remove_path(symlink_third_party_dir)
            print(f"[SPEAR | create_sybmolic_links.py]     Creating symlink: {symlink_third_party_dir} -> {third_party_dir}")
            os.symlink(third_party_dir, symlink_third_party_dir)
            print()

    assert os.path.exists(unreal_project_dir)
    _, project = os.path.split(unreal_project_dir)
    uproject = os.path.realpath(os.path.join(unreal_project_dir, project + ".uproject"))
    assert os.path.exists(uproject)

    print(f"[SPEAR | create_sybmolic_links.py] Found uproject: {uproject}")

    # create a symlink to Engine/Content/StarterContent
    symlink_starter_content_dir = os.path.join(unreal_project_dir, "Content", "StarterContent") # don't want os.path.realpath here
    if spear.path_exists(symlink_starter_content_dir):
        print(f"[SPEAR | create_sybmolic_links.py]     File or directory or symlink exists, removing: {symlink_starter_content_dir}")
        spear.remove_path(symlink_starter_content_dir)
    print(f"[SPEAR | create_sybmolic_links.py]     Creating symlink: {symlink_starter_content_dir} -> {starter_content_dir}")
    os.symlink(starter_content_dir, symlink_starter_content_dir)

    # create a symlink to third_party
    symlink_third_party_dir = os.path.join(unreal_project_dir, "ThirdParty") # don't want os.path.realpath here
    if spear.path_exists(symlink_third_party_dir):
        print(f"[SPEAR | create_sybmolic_links.py]     File or directory or symlink exists, removing: {symlink_third_party_dir}")
        spear.remove_path(symlink_third_party_dir)
    print(f"[SPEAR | create_sybmolic_links.py]     Creating symlink: {symlink_third_party_dir} -> {third_party_dir}")
    os.symlink(third_party_dir, symlink_third_party_dir)

    # get list of plugins from the uproject file
    with open(os.path.realpath(os.path.join(unreal_project_dir, project + ".uproject"))) as f:
        project_plugins = [ p["Name"] for p in json.load(f)["Plugins"] ]
    print(f"[SPEAR | create_sybmolic_links.py]     Plugin dependencies: {project_plugins}")

    # create a Plugins dir in the project dir
    project_plugins_dir = os.path.realpath(os.path.join(unreal_project_dir, "Plugins"))
    os.makedirs(project_plugins_dir, exist_ok=True)

    # create symlink for each plugin listed in the project, if the plugin is in our unreal_plugins dir
    for project_plugin in project_plugins:
        if project_plugin in unreal_plugins:
            print("%S",project_plugin)
            plugin_dir = os.path.realpath(os.path.join(unreal_plugins_dir, project_plugin))
            symlink_plugin_dir = os.path.join(project_plugins_dir, project_plugin) # don't want os.path.realpath here
            if spear.path_exists(symlink_plugin_dir):
                print(f"[SPEAR | create_sybmolic_links.py]         File or directory or symlink exists, removing: {symlink_plugin_dir}")
                spear.remove_path(symlink_plugin_dir)
            print(f"[SPEAR | create_sybmolic_links.py]         Creating symlink: {symlink_plugin_dir} -> {plugin_dir}")
            os.symlink(plugin_dir, symlink_plugin_dir)
        else:
            print(f"[SPEAR | create_sybmolic_links.py]         {project} depends on {project_plugin}, but this plugin is not in {unreal_plugins_dir}, so we do not attempt to create a symlink...")

    print("[SPEAR | create_sybmolic_links.py] Done.")
